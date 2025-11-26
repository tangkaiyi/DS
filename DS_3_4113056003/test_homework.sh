#!/bin/bash

# =================設定區域=================
STUDENT_ID="4113056003"     # 學號
TOTAL_TASKS=4               # 總共有幾個程式
CXX="g++"                   # 編譯器
CXXFLAGS="-O2 -std=c++11"   # 編譯參數

# 1. 設定每個任務的時間限制 (對應 DS1 到 DS4)
TIME_LIMITS=("8.0s" "8.0s" "20.0s" "8.0s")

# 2. 設定每個任務的配分 (總分建議為 100)
# 例如: 第1題 25分, 第2題 25分...
TASK_SCORES=(10 30 30 30)
# =========================================

# 定義顏色
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
CYAN="\033[0;36m"
NC="\033[0m" # No Color

# 初始化總分
CURRENT_TOTAL_SCORE=0

echo "========================================"
echo " 自動評測系統 (ID: $STUDENT_ID)"
echo "========================================"

for i in $(seq 1 $TOTAL_TASKS); do
    SRC_FILE="DS${i}_${STUDENT_ID}.cpp"
    EXE_FILE="DS${i}.out"
    OUTPUT_FILE="output${i}.txt"
    INPUT_FILE="testcase${i}.txt"
    
    # 計算陣列索引 (從 0 開始)
    INDEX=$(($i - 1))
    
    # 取得該題設定
    CURRENT_LIMIT=${TIME_LIMITS[$INDEX]}
    CURRENT_SCORE=${TASK_SCORES[$INDEX]}
    
    # 防呆預設值
    [ -z "$CURRENT_LIMIT" ] && CURRENT_LIMIT="1s"
    [ -z "$CURRENT_SCORE" ] && CURRENT_SCORE=0

    # 自動偵測答案檔名
    if [ -f "ans${i}.txt" ]; then
        ANS_FILE="ans${i}.txt"
    else
        ANS_FILE="ans${i}"
    fi

    echo ""
    echo "----------------------------------------"
    printf "[ 任務 #%d ] 配分: %d 分 | 限時: %s\n" "$i" "$CURRENT_SCORE" "$CURRENT_LIMIT"
    echo "----------------------------------------"

    # 1. 檢查檔案存在
    if [ ! -f "$SRC_FILE" ]; then
        printf "${RED}錯誤: 找不到原始碼 $SRC_FILE${NC} (0 分)\n"
        continue
    fi
    if [ ! -f "$INPUT_FILE" ]; then
        printf "${RED}錯誤: 找不到測資檔 $INPUT_FILE${NC} (0 分)\n"
        continue
    fi

    # 2. 編譯
    $CXX $CXXFLAGS "$SRC_FILE" -o "$EXE_FILE"
    if [ $? -ne 0 ]; then
        printf "${RED}編譯失敗 (Compile Error)${NC} (0 分)\n"
        continue
    fi

    # 3. 執行 (Time Limit Check)
    printf "執行中... "
    START_TIME=$(date +%s.%N)
    
    timeout "$CURRENT_LIMIT" ./"$EXE_FILE"
    EXIT_CODE=$? 
    
    END_TIME=$(date +%s.%N)
    ELAPSED=$(echo "$END_TIME - $START_TIME" | bc)

    # 4. 判斷執行狀態與計分
    TASK_RESULT_SCORE=0 # 預設該題 0 分

    if [ $EXIT_CODE -eq 124 ]; then
        printf "${RED}TLE (時間限制逾時)${NC}\n"
    elif [ $EXIT_CODE -ne 0 ]; then
        printf "${RED}RE (執行期錯誤) 代碼: $EXIT_CODE${NC}\n"
    else
        printf "耗時: ${YELLOW}%.4f 秒${NC}\n" $ELAPSED
        
        # 5. 比對答案
        if [ -f "$OUTPUT_FILE" ] && [ -f "$ANS_FILE" ]; then
            diff -wB "$OUTPUT_FILE" "$ANS_FILE" > /dev/null
            
            if [ $? -eq 0 ]; then
                printf "結果: ${GREEN}AC (Accepted)${NC} -> 獲得 ${GREEN}+${CURRENT_SCORE} 分${NC}\n"
                TASK_RESULT_SCORE=$CURRENT_SCORE
            else
                printf "結果: ${RED}WA (Wrong Answer)${NC}\n"
                echo "--- 差異預覽 ---"
                diff -wB "$OUTPUT_FILE" "$ANS_FILE" | head -n 5
            fi
        else
             printf "${RED}比對失敗 (找不到輸出或答案檔)${NC}\n"
        fi
    fi
    
    # 累加分數
    CURRENT_TOTAL_SCORE=$(($CURRENT_TOTAL_SCORE + $TASK_RESULT_SCORE))

    # 清理執行檔
    rm -f "$EXE_FILE"
done

echo ""
echo "========================================"
echo -e " 評測結束"
if [ $CURRENT_TOTAL_SCORE -eq 100 ]; then
    echo -e " 最終總分: ${GREEN}${CURRENT_TOTAL_SCORE} / 100${NC}"
else
    echo -e " 最終總分: ${CYAN}${CURRENT_TOTAL_SCORE} / 100${NC}"
fi
echo "========================================"