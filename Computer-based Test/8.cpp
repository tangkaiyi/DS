#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<char>nodes;
int stations;

struct TreeNode{
    int data;
    TreeNode *right;
    TreeNode *left;
    TreeNode(int x): data(x), left(NULL),right(NULL) {}
};

TreeNode* buildTree(){
    if(nodes.empty() || nodes[0] == 'N') return NULL;
    TreeNode* root = new TreeNode(0);
    queue<TreeNode*>q;
    q.push(root);

    int i=1;
    while(!q.empty() && i<nodes.size()){
        TreeNode *curr = q.front();
        q.pop();

        if(i<nodes.size() && nodes[i] != 'N'){
            curr->left = new TreeNode(0);
            q.push(curr->left);
        }
        i++;
        if(i<nodes.size() && nodes[i] != 'N'){
            curr->right = new TreeNode(0);
            q.push(curr->right);
        }
        i++;

    }
    return root;
}

int dfs(TreeNode *node){
    if(!node) return 0;

    int leftstate = dfs(node->left);
    int rightstate = dfs(node->right);

    if(leftstate == 2 || rightstate == 2){
        stations++;
        return 1;
    }
    if(leftstate == 1 || rightstate == 1){
        return 0;
    }

    return 2;
}

void solve_case(){
    nodes.clear();
    stations = 0;
    string s;
    cin >> s;
    for(char c:s){
        if(c == '0' || c == 'N') nodes.push_back(c);
    }
    TreeNode *root = buildTree();
    int rootstate = dfs(root);
    if(rootstate == 2){
        stations++;
    }
    cout << stations << endl;
}

int main(){
    freopen("testcase8.txt","r",stdin);
    freopen("output8.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}