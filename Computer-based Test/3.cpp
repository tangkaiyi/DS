#include <iostream> 
#include <vector>
#include <deque>
#include <tuple> 

using namespace std;

void solove_case(){
    int m,n;
    cin >> m >> n;
    bool possible = false;
    vector<vector<int>> grid(m,vector<int>(n));
    int start_pr,start_pc,start_er,start_ec,target_r,target_c;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
            if(grid[i][j] == 2) {
                start_pr = i;
                start_pc = j;
            }
            else if(grid[i][j] == 3){
                start_er = i;
                start_ec = j;
            }
            else if(grid[i][j] == 4){
                target_r = i;
                target_c = j;
            }
        }
    }
    vector<vector<vector<vector<bool>>>> visited(m,vector<vector<vector<bool>>>(n,vector<vector<bool>>(m,vector<bool>(n,false))));
    int dr[] = {-1,0,1,0}; // left , up , right , down
    int dc[] = {0,1,0,-1};

    deque<tuple<int,int,int,int,int>> dq; // steps,pr,pc,er,ec

    dq.push_front({0,start_pr,start_pc,start_er,start_ec});
    visited[start_pr][start_pc][start_er][start_ec] = true;

    while(!dq.empty()){
        tuple<int,int,int,int,int> current = dq.front();
        dq.pop_front();

        int pushes = get<0>(current);
        int pr = get<1>(current);
        int pc = get<2>(current);
        int er = get<3>(current);
        int ec = get<4>(current);

        if(er == target_r && ec == target_c){
            cout << pushes << endl;
            possible = true;
            break;
        }

        for(int i=0;i<4;i++){
            int npr = pr+dr[i];
            int npc = pc+dc[i];

            if(npr>=0 && npr<m && npc>=0 && npc<n && grid[npr][npc] != 1 && !(npr == er && npc == ec)){
                if(!visited[npr][npc][er][ec]){
                    visited[npr][npc][er][ec] = true;
                    dq.push_front({pushes,npr,npc,er,ec});
                }
            }
        }

        for(int i=0;i<4;i++){
            if(pr+dr[i] == er && pc+dc[i] == ec){
                int new_er = er+dr[i];
                int new_ec = ec+dc[i];

                if(new_er>=0 && new_er<m && new_ec>=0 && new_ec<n && grid[new_er][new_ec] != 1){
                    if(!visited[er][ec][new_er][new_ec]){
                        visited[er][ec][new_er][new_ec] = true;
                        dq.push_back({pushes+1,er,ec,new_er,new_ec});
                    }
                }
            }
        }
    }
    if(!possible) cout << -1 << endl;

}

int main(){
    freopen("testcase3.txt","r",stdin);
    freopen("output3.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    
    while(t--){
        solove_case();
    }
    return 0;
}