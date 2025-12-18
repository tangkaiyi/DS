import sys
import os
import difflib

# 設定顏色代碼 (讓終端機輸出比較漂亮)
class Colors:
    GREEN = '\033[92m'
    RED = '\033[91m'
    RESET = '\033[0m'
    YELLOW = '\033[93m'

def read_file(file_path):
    """讀取檔案並標準化內容（去除前後空白、統一換行符）"""
    if not os.path.exists(file_path):
        print(f"{Colors.RED}錯誤: 找不到檔案 {file_path}{Colors.RESET}")
        sys.exit(1)
    
    with open(file_path, 'r', encoding='utf-8') as f:
        # readlines() 讀取所有行
        lines = f.readlines()
        
    # 標準化處理：去除每行右邊的空白與換行符號
    # 這樣可以避免因為 ' ' 或 '\r\n' 造成的誤判
    return [line.rstrip() for line in lines]

def compare_files(user_output_file, answer_file):
    """比對兩個檔案"""
    user_lines = read_file(user_output_file)
    ans_lines = read_file(answer_file)
    
    # 1. 完全相同的情況
    if user_lines == ans_lines:
        print(f"{Colors.GREEN}✅ Accepted (AC): 答案完全正確！{Colors.RESET}")
        return True

    # 2. 如果不相同，顯示差異
    print(f"{Colors.RED}❌ Wrong Answer (WA): 發現差異{Colors.RESET}")
    print("-" * 40)
    
    # 使用 difflib 產生差異報告
    diff = difflib.unified_diff(
        user_lines, 
        ans_lines, 
        fromfile='您的輸出', 
        tofile='正確答案', 
        lineterm=''
    )
    
    # 印出差異行
    for line in diff:
        if line.startswith('+'):
            print(f"{Colors.GREEN}{line}{Colors.RESET}") # 正確答案有的 (綠色)
        elif line.startswith('-'):
            print(f"{Colors.RED}{line}{Colors.RESET}")   # 你的輸出有的 (紅色)
        elif line.startswith('^'): 
            print(f"{Colors.YELLOW}{line}{Colors.RESET}")
        else:
            print(line)
            
    print("-" * 40)
    return False

if __name__ == "__main__":
    # 使用方式檢查
    if len(sys.argv) != 3:
        print("使用方式: python check_answer.py <你的輸出檔案> <正確答案檔案>")
        print("範例: python check_answer.py my_output.txt answer.txt")
        sys.exit(1)

    user_file = sys.argv[1]
    ans_file = sys.argv[2]

    compare_files(user_file, ans_file)