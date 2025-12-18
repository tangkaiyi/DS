#include <iostream>
#include <vector>
#include <deque>
#include <tuple>

using namespace std;

void solve_case(){
    int m,n;
    cin >> m >> n;
    bool possible = false;
    int ans;
    vector<vector<int>> grid(m,vector<int>(n));
    int start_pr,start_pc,start_er,start_ec,target_r,target_c;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
            if(grid[i][j] == 2) start_pr = i, start_pc = j;
            if(grid[i][j] == 3) start_er = i, start_ec = j;
            if(grid[i][j] == 4) target_r = i, target_c = j;
        }
    }
    int dr[] = {-1,0,1,0};
    int dc[] = {0,1,0,-1};

    vector<vector<vector<vector<bool>>>> visited(m,vector<vector<vector<bool>>>(n,vector<vector<bool>>(m,vector<bool>(n,false))));
    deque<tuple<int,int,int,int,int>> dq; 
    dq.push_front({0,start_pr,start_pc,start_er,start_ec});
    visited[start_pr][start_pc][start_er][start_ec] = true;

    while(!dq.empty()){
        tuple<int,int,int,int,int> current = dq.front();
        dq.pop_front();

        int push = get<0>(current);
        int pr = get<1>(current);
        int pc = get<2>(current);
        int er = get<3>(current);
        int ec = get<4>(current);

        if(er == target_r && ec == target_c){
            possible = true;
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
            if(er == pr+dr[i] && ec == pc+dc[i]){
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
    if(possible) cout << ans << endl;
    else cout << -1 << endl;
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