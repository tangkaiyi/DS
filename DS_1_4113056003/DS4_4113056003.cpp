#include <iostream>
#include <vector>
#include <queue>    
#include <tuple>   
#include <cstdio>  

using namespace std;

int solve_case() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n));
    int start_pr, start_pc, start_cr, start_cc, target_r, target_c;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) start_pr = i, start_pc = j;
            else if (grid[i][j] == 3) start_cr = i, start_cc = j;
            else if (grid[i][j] == 4) target_r = i, target_c = j; 
        }
    }

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    deque<tuple<int, int, int, int, int>> dq;

    vector<vector<vector<vector<bool>>>> visited(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>(m, vector<bool>(n, false))));

    dq.push_front({0, start_pr, start_pc, start_cr, start_cc});
    visited[start_pr][start_pc][start_cr][start_cc] = true;
    
    while (!dq.empty()) {

        tuple<int, int, int, int, int> current_state = dq.front();
        dq.pop_front();

        int pushes = get<0>(current_state);
        int pr = get<1>(current_state);
        int pc = get<2>(current_state);
        int cr = get<3>(current_state);
        int cc = get<4>(current_state);

        if (cr == target_r && cc == target_c) {
            return pushes;
        }

        for (int i = 0; i < 4; ++i) {
            int npr = pr + dr[i];
            int npc = pc + dc[i];

            if (npr >= 0 && npr < m && npc >= 0 && npc < n && grid[npr][npc] != 1 && !(npr == cr && npc == cc)) {
                if (!visited[npr][npc][cr][cc]) {
                    visited[npr][npc][cr][cc] = true;
                    dq.push_front({pushes, npr, npc, cr, cc});
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            if (pr + dr[i] == cr && pc + dc[i] == cc) {
                 int new_cr = cr + dr[i];
                 int new_cc = cc + dc[i];

                 if (new_cr >= 0 && new_cr < m && new_cc >= 0 && new_cc < n && grid[new_cr][new_cc] != 1) {

                     if (!visited[cr][cc][new_cr][new_cc]) {
                         visited[cr][cc][new_cr][new_cc] = true;
                         dq.push_back({pushes + 1, cr, cc, new_cr, new_cc});
                     }
                 }
            }
        }
    }

    return -1;
}

int main() {
    if(freopen("testcase4.txt", "r", stdin)==NULL) return -1;
    if(freopen("output4.txt", "w", stdout)==NULL) return -1;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        cout << solve_case() << "\n";
    }
    return 0;
}
