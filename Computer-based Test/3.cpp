#include <iostream>
#include <vector>
#include <deque>
#include <tuple>

using namespace std;

void solve_case(){
    int m,n;
    cin >> m >> n;
    int ans = -1;
    vector<vector<int>> grid(m,vector<int>(n));
    int start_pr,start_pc,start_er,start_ec,target_r,target_c;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
            if(grid[i][j] == 2) start_pr=i,start_pc=j;
            if(grid[i][j] == 3) start_er=i,start_ec=j;
            if(grid[i][j] == 4) target_r=i,target_c=j;
        }
    }
    int dr[] = {-1,0,1,0};
    int dc[] = {0,1,0,-1};

    vector<vector<vector<vector<bool>>>> visited(m,vector<vector<vector<bool>>>(n,vector<vector<bool>>(m,vector<bool>(n,false))));
    deque<tuple<int,int,int,int,int>>dq;
    dq.push_front({0,start_pr,start_pc,start_er,start_ec});
    visited[start_pr][start_pc][start_er][start_ec] = true;

    while(!dq.empty()){
        auto curr = dq.front();
        dq.pop_front();

        int push = get<0>(curr);
        int pr = get<1>(curr);
        int pc = get<2>(curr);
        int er = get<3>(curr);
        int ec = get<4>(curr);

        if(er == target_r && ec == target_c){
            ans = push;
            break;
        }

        for(int i=0;i<4;i++){
            int npr = pr+dr[i];
            int npc = pc+dc[i];
            if(npr>=0 && npr<m && npc>=0 && npc<n && grid[npr][npc] != 1 && !(npr == er && npc == ec)){
                if(!visited[npr][npc][er][ec]){
                    visited[npr][npc][er][ec] = true;
                    dq.push_front({push,npr,npc,er,ec});
                }
            }
        }
        for(int i=0;i<4;i++){
            if(pr+dr[i] == er && pc+dc[i] == ec){
                int ner = er+dr[i];
                int nec = ec+dc[i];
                if(ner>=0 && ner<m && nec>=0 && nec<n && grid[ner][nec] != 1){
                    if(!visited[er][ec][ner][nec]){
                        visited[er][ec][ner][nec] = true;
                        dq.push_back({push+1,er,ec,ner,nec});
                    }
                }
            }
        }

    }
    cout << ans << endl;
}

int main(){
    freopen("testcase3.txt","r",stdin);
    freopen("output3.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}