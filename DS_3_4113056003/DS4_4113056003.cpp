#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 500005;

struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(NULL), right(NULL) {}
};

int inPos[MAXN];
int levelPos[MAXN];
int st[MAXN][20];
int logs[MAXN];
int subtreeSize[MAXN];
Node* nodePtrs[MAXN];

void buildST(int n, const vector<int>& inorder) {
    logs[1] = 0;
    for (int i = 2; i <= n; i++) logs[i] = logs[i/2] + 1;
    
    for (int i = 0; i < n; i++) {
        st[i][0] = i;
    }
    
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            int idx1 = st[i][j-1];
            int idx2 = st[i + (1 << (j-1))][j-1];
            
            if (levelPos[inorder[idx1]] < levelPos[inorder[idx2]])
                st[i][j] = idx1;
            else
                st[i][j] = idx2;
        }
    }
}

int queryST(int L, int R, const vector<int>& inorder) {
    int j = logs[R - L + 1];
    int idx1 = st[L][j];
    int idx2 = st[R - (1 << j) + 1][j];
    if (levelPos[inorder[idx1]] < levelPos[inorder[idx2]]) return idx1;
    else return idx2;
}

Node* buildTree(int L, int R, const vector<int>& inorder) {
    if (L > R) return NULL;
    
    int rootIdx = queryST(L, R, inorder);
    int rootVal = inorder[rootIdx];
    
    Node* root = new Node(rootVal);
    nodePtrs[rootVal] = root;
    
    root->left = buildTree(L, rootIdx - 1, inorder);
    root->right = buildTree(rootIdx + 1, R, inorder);
    
    return root;
}

int countSize(Node* u) {
    if (!u) return 0;
    int s = 1 + countSize(u->left) + countSize(u->right);
    subtreeSize[u->val] = s;
    return s;
}

int main() {
    if (freopen("testcase4.txt", "r", stdin) == NULL) {
       fprintf(stderr, "Error: Input file not found\n");
    return 1;
    }
    if (freopen("output4.txt", "w", stdout) == NULL) {
        fprintf(stderr, "Error: Unable to create output file\n");
        return 1;
    }
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            int targetX;
            cin >> targetX;
            
            int n;
            cin >> n;
            
            vector<int> inorder(n);
            for(int i=0; i<n; ++i) {
                cin >> inorder[i];
                inPos[inorder[i]] = i;
            }
            
            vector<int> levelOrder(n);
            for(int i=0; i<n; ++i) {
                cin >> levelOrder[i];
                levelPos[levelOrder[i]] = i;
            }
            
            buildST(n, inorder);
            Node* root = buildTree(0, n-1, inorder);
            
            countSize(root);
            
            bool canWin = false;
            Node* xNode = nodePtrs[targetX];
            
            if (xNode) {
                int lSize = (xNode->left) ? subtreeSize[xNode->left->val] : 0;
                int rSize = (xNode->right) ? subtreeSize[xNode->right->val] : 0;
                int pSize = n - subtreeSize[targetX];
                
                if (lSize > n/2 || rSize > n/2 || pSize > n/2) {
                    canWin = true;
                }
            }
            
            cout << (canWin ? "1" : "0") << "\n";
        }
    }
    return 0;
}