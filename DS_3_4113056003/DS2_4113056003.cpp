#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<char> nodes;
int stations;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int dfs(TreeNode* node){
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

TreeNode* buildTree(){
    if(nodes.empty() || nodes[0] == 'N') return nullptr;

    TreeNode* root = new TreeNode(0);
    queue<TreeNode*> q;
    q.push(root);

    int i=1;
    while(!q.empty() && i<nodes.size()){
        TreeNode* current = q.front();
        q.pop();

        if(i<nodes.size() && nodes[i] != 'N'){
            current->left = new TreeNode(0);
            q.push(current->left);
        }
        i++;

        if(i<nodes.size() && nodes[i] != 'N'){
            current->right = new TreeNode(0);
            q.push(current->right);
        }
        i++;
    }
    return root;

}

void solve_case(){
    string s;
    cin >> s;
    nodes.clear();
    stations = 0;    
    for(char c:s){
        if(c == 'N' || c == '0'){
            nodes.push_back(c);
        }
    }
    TreeNode* root = buildTree();
    if(root){
        int rootstate = dfs(root);
        if(rootstate == 2) stations++;    
    }

    cout << stations << "\n";


}

int main(){
    if(!freopen("testcase2.txt","r",stdin)) return -1;
    if(!freopen("output2.txt","w",stdout)) return -1;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}