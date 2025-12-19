#include <iostream>
#include <vector>

using namespace std;

int inorder[500001];
int preorder[500001];
int inorder_pos[500001];

struct TreeNode{
    int data;
    TreeNode *left,*right,*parent;
};

TreeNode* buildTree(int inStart,int inEnd,int preStart,int preEnd,vector<TreeNode*>* node){
    if(inStart>inEnd || preStart>preEnd) return NULL;

    int root = preorder[preStart];
    TreeNode* curr = (*node)[root];
    int inIndex = inorder_pos[root];
    int leftsize = inIndex-inStart;

    curr->left = buildTree(inStart,inIndex-1,preStart+1,preStart+leftsize,node);
    curr->right = buildTree(inIndex+1,inEnd,preStart+leftsize+1,preEnd,node);
    if(curr->left) curr->left->parent = curr;
    if(curr->right) curr->right->parent = curr;

    return curr;
}

void fill(TreeNode* node){
    if(!node) return;
    if(node->data == 1) return;
    node->data = 1;
    fill(node->left);
    fill(node->right);
}

void sip(TreeNode *node){
    if(!node) return;
    if(node->data == 0) return;
    node->data = 0;
    sip(node->parent);
}

int check(TreeNode *node){
    return node->data;
}

void solve_case(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> inorder[i];
        inorder_pos[inorder[i]] = i;
    }
    for(int i=0;i<n;i++){
        cin >> preorder[i];
    }
    vector<TreeNode*> node(n+1);
    for(int i=0;i<=n;i++){
        node[i] = new TreeNode();
        node[i]->data = 0;
    }
    TreeNode *root = buildTree(0,n-1,0,n-1,&node);
    int q;
    cin >> q;
    while(q--){
        int c,v;
        cin >> c >> v;
        if(c == 1) fill(node[v]);
        if(c == 2) sip(node[v]);
        if(c == 3) cout << check(node[v]) << endl;
    }

}

int main(){
    freopen("testcase9.txt","r",stdin);
    freopen("output9.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin>> t;
    while(t--){
        solve_case();
    }
    return 0;
}