#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
vector<int> adj[MAXN];
int inTime[MAXN], outTime[MAXN];
int timer;
int posMap[MAXN];

int treeFill[4 * MAXN];
int lazyFill[4 * MAXN];

void pushDownFill(int node) {
    if (lazyFill[node] != 0) {
        treeFill[2 * node] = lazyFill[node];
        lazyFill[2 * node] = lazyFill[node];
        treeFill[2 * node + 1] = lazyFill[node];
        lazyFill[2 * node + 1] = lazyFill[node];
        lazyFill[node] = 0;
    }
}

void updateFill(int node, int start, int end, int l, int r, int val) {
    if (l > end || r < start) return;
    if (l <= start && end <= r) {
        treeFill[node] = val;
        lazyFill[node] = val;
        return;
    }
    pushDownFill(node);
    int mid = (start + end) / 2;
    updateFill(2 * node, start, mid, l, r, val);
    updateFill(2 * node + 1, mid + 1, end, l, r, val);
}

int queryFill(int node, int start, int end, int idx) {
    if (start == end) return treeFill[node];
    pushDownFill(node);
    int mid = (start + end) / 2;
    if (idx <= mid) return queryFill(2 * node, start, mid, idx);
    else return queryFill(2 * node + 1, mid + 1, end, idx);
}

int treeSip[4 * MAXN];

void updateSip(int node, int start, int end, int idx, int val) {
    if (start == end) {
        treeSip[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) updateSip(2 * node, start, mid, idx, val);
    else updateSip(2 * node + 1, mid + 1, end, idx, val);
    treeSip[node] = max(treeSip[2 * node], treeSip[2 * node + 1]);
}

int querySip(int node, int start, int end, int l, int r) {
    if (l > end || r < start) return 0;
    if (l <= start && end <= r) return treeSip[node];
    int mid = (start + end) / 2;
    return max(querySip(2 * node, start, mid, l, r),
               querySip(2 * node + 1, mid + 1, end, l, r));
}

int build(int inStart, int inEnd, int* inorder, int* preorder, int& preIdx) {
    if (inStart > inEnd) return 0;
    int rootVal = preorder[preIdx++];
    int inIdx = posMap[rootVal];
    
    int leftChild = build(inStart, inIdx - 1, inorder, preorder, preIdx);
    int rightChild = build(inIdx + 1, inEnd, inorder, preorder, preIdx);
    
    if (leftChild) adj[rootVal].push_back(leftChild);
    if (rightChild) adj[rootVal].push_back(rightChild);
    
    return rootVal;
}

void dfs(int u) {
    inTime[u] = ++timer;
    for (int v : adj[u]) {
        dfs(v);
    }
    outTime[u] = timer;
}

int inorder[MAXN], preorder[MAXN];

int main() {
    if (freopen("testcase3.txt", "r", stdin) == NULL) {
       fprintf(stderr, "Error: Input file not found\n");
    return 1;
    }
    if (freopen("output3.txt", "w", stdout) == NULL) {
        fprintf(stderr, "Error: Unable to create output file\n");
        return 1;
    }
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            
            for(int i=1; i<=n; ++i) adj[i].clear();
            for(int i=0; i<=4*n; ++i) {
                treeFill[i] = 0; lazyFill[i] = 0; treeSip[i] = 0;
            }
            timer = 0;

            for (int i = 0; i < n; i++) { cin >> inorder[i]; posMap[inorder[i]] = i; }
            for (int i = 0; i < n; i++) { cin >> preorder[i]; }

            int preIdx = 0;
            int root = build(0, n - 1, inorder, preorder, preIdx);
            dfs(root);

            int q;
            cin >> q;
            for (int t = 1; t <= q; t++) {
                int type, node;
                cin >> type >> node;
                if (type == 1) {
                    updateFill(1, 1, n, inTime[node], outTime[node], t);
                }
                else if (type == 2) {
                    updateSip(1, 1, n, inTime[node], t);
                }
                else {
                    int lastFill = queryFill(1, 1, n, inTime[node]);
                    int lastSip = querySip(1, 1, n, inTime[node], outTime[node]);
                    if (lastFill > lastSip) cout << "1\n";
                    else cout << "0\n";
                }
            }
        }
    }
    return 0;
}