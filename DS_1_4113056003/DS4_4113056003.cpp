#include <iostream>
#include <vector>
#include <queue>    // For std::deque
#include <tuple>    // For std::tuple and std::get
#include <cstdio>   // For freopen

using namespace std;

// Solves "4 Minimum Pushes to Exit the Ruin"
int solve_case() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n));
    int start_pr, start_pc, start_cr, start_cc, target_r, target_c;

    // Read the grid and find the starting positions of the pioneer, core, and spaceship
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) start_pr = i, start_pc = j;       // Pioneer's start [cite: 125]
            else if (grid[i][j] == 3) start_cr = i, start_cc = j;  // Core's start [cite: 126]
            else if (grid[i][j] == 4) target_r = i, target_c = j; // Spaceship (target) [cite: 127]
        }
    }

    // Directions for movement: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // The deque for our 0-1 BFS. State is stored as a tuple.
    // State: {pushes, pioneer_row, pioneer_col, core_row, core_col}
    deque<tuple<int, int, int, int, int>> dq;
    
    // 4D visited array to prevent cycles: visited[pr][pc][cr][cc]
    vector<vector<vector<vector<bool>>>> visited(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>(m, vector<bool>(n, false))));

    // Push the initial state onto the front of the deque.
    dq.push_front({0, start_pr, start_pc, start_cr, start_cc});
    visited[start_pr][start_pc][start_cr][start_cc] = true;
    
    while (!dq.empty()) {
        // Get the current state from the front of the deque
        auto current_state = dq.front();
        dq.pop_front();

        // Unpack the tuple into individual variables
        int pushes = get<0>(current_state);
        int pr = get<1>(current_state);
        int pc = get<2>(current_state);
        int cr = get<3>(current_state);
        int cc = get<4>(current_state);
        
        // If the core has reached the spaceship, we have found the solution
        if (cr == target_r && cc == target_c) {
            return pushes;
        }

        // --- Action 1: Pioneer moves (cost 0) -> add to front of deque ---
        for (int i = 0; i < 4; ++i) {
            int npr = pr + dr[i]; // New pioneer row
            int npc = pc + dc[i]; // New pioneer col

            // Check if the new position is valid: in-bounds, not a wall, and not on the core
            if (npr >= 0 && npr < m && npc >= 0 && npc < n && grid[npr][npc] != 1 && !(npr == cr && npc == cc)) {
                if (!visited[npr][npc][cr][cc]) {
                    visited[npr][npc][cr][cc] = true;
                    dq.push_front({pushes, npr, npc, cr, cc});
                }
            }
        }

        // --- Action 2: Pioneer pushes core (cost 1) -> add to back of deque ---
        for (int i = 0; i < 4; ++i) {
            // Check if the pioneer is adjacent to the core in this direction
            if (pr + dr[i] == cr && pc + dc[i] == cc) {
                 // Calculate the core's potential new position
                 int new_cr = cr + dr[i];
                 int new_cc = cc + dc[i];

                 // Check if the push is valid: new position is in-bounds and not a wall
                 if (new_cr >= 0 && new_cr < m && new_cc >= 0 && new_cc < n && grid[new_cr][new_cc] != 1) {
                     // The new state: pioneer moves into the core's old spot, core moves to the new spot
                     if (!visited[cr][cc][new_cr][new_cc]) {
                         visited[cr][cc][new_cr][new_cc] = true;
                         dq.push_back({pushes + 1, cr, cc, new_cr, new_cc});
                     }
                 }
            }
        }
    }
    
    // If the deque becomes empty and the target was not reached, it's impossible.
    return -1;
}

int main() {
    // Redirect I/O to files as per homework instructions
    freopen("testcase4.txt", "r", stdin);
    freopen("output4.txt", "w", stdout);

    // Speed up C++ I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        cout << solve_case() << "\n";
    }
    return 0;
}