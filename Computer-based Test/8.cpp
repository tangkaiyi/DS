#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<char> node;
int stations;

struct TreeNode{
    int data;
    TreeNode *left,*right;
    TreeNode(int x): data(x),left(NULL),right(NULL){};
};

int dfs(TreeNode* node){
    if(node == NULL) return 0;

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

TreeNode* buildTree(){
    if(node.empty() || node[0] == 'N') return NULL;

    TreeNode *root = new TreeNode(0);
    queue<TreeNode*> q;
    q.push(root);

    int i=1;
    while(!q.empty()){
        TreeNode *curr = q.front();
        q.pop();

        if(i<node.size() && node[i] != 'N'){
            curr->left = new TreeNode(0);
            q.push(curr->left);
        }
        i++;
        if(i<node.size() && node[i] != 'N'){
            curr->right = new TreeNode(0);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

void solve_case(){
    node.clear();
    stations = 0;
    string s;
    cin >> s;
    for(char c:s){
        if(c =='0' || c == 'N') node.push_back(c);
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