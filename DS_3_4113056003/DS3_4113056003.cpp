    #include <iostream>
    #include <vector>

    using namespace std;

    int inorder[500001];
    int preorder[500001];
    int inorder_pos[500001];

    struct TreeNode{
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        TreeNode(int x) : val(x), left(NULL), right(NULL) ,parent(NULL) {}
    };

    TreeNode* buildTree(int inStart,int inEnd,int preStart,int preEnd,vector<TreeNode*>* nodes){
        if(inStart>inEnd || preStart>preEnd) return nullptr;
        
        int root = preorder[preStart];
        TreeNode* rootNode = (*nodes)[root];

        int inIndex = inorder_pos[root];
        int leftsize = inIndex - inStart;

        rootNode->left = buildTree(inStart,inIndex-1,preStart+1,preStart+leftsize,nodes);
        rootNode->right = buildTree(inIndex+1,inEnd,preStart+leftsize+1,preEnd,nodes);
        if (rootNode->left) rootNode->left->parent = rootNode;
        if (rootNode->right) rootNode->right->parent = rootNode;
        return rootNode;
    }

    void fill(TreeNode* node,vector<TreeNode*>* nodes){
        if(!node) return;
        node->val = 1;
        if(node->left) fill(node->left,nodes);
        if(node->right) fill(node->right,nodes);
    }

    void sip(TreeNode* node,vector<TreeNode*>* nodes){
        if(!node) return;
        node->val = 0;
        if(node->parent) sip(node->parent,nodes);
    }

    void determine(TreeNode* node){
        cout << node->val << "\n";
    }

    void solve_case(){
        int n;
        cin >> n;
        vector<TreeNode*> nodes(n+1, nullptr);
        for (int i = 1; i <= n; ++i) {
            nodes[i] = new TreeNode(0);
        }

        for(int i=0;i<n;i++){
            int temp;
            cin >> temp;
            inorder[i] = temp;
            inorder_pos[inorder[i]] = i;
        }
        for(int i=0;i<n;i++){
            int temp;
            cin >> temp;
            preorder[i] = temp;
        }

        TreeNode* root = buildTree(0,n-1,0,n-1,&nodes);
        int c,v,q;
        cin >> q;
        for(int i=0;i<q;i++){
            cin>> c >> v;
            TreeNode* node = nodes[v];
            if(c == 1){
                fill(node,&nodes);
            }
            else if(c == 2){
                sip(node,&nodes);
            }
            else{
                determine(node);
            }
        }

        for (int i = 1; i <= n; ++i) {
            delete nodes[i];
        }
    }

    int main(){
        if(!freopen("testcase3.txt","r",stdin)) return -1;
        if(!freopen("output3.txt","w",stdout)) return -1;

        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        int t;
        cin >> t;
        while(t--){
            solve_case();
        }
        return 0;
    }