#include <iostream>

using namespace std;

int inorder[500001];
int postorder[500001];
int inorder_pos[600001];

void preorder_print(int inStart,int inEnd,int postStart,int postEnd){
    if(inStart>inEnd || postStart>postEnd) return;
    
    int root = postorder[postEnd];
    cout << root << " ";
    int inIndex = inorder_pos[root];
    int leftsize = inIndex-inStart;

    preorder_print(inStart,inIndex-1,postStart,postStart+leftsize-1);
    preorder_print(inIndex+1,inEnd,postStart+leftsize,postEnd-1);
}

void solve_case(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> inorder[i];
        inorder_pos[inorder[i]] = i;
    }
    for(int i=0;i<n;i++){
        cin >> postorder[i];
    }
    preorder_print(0,n-1,0,n-1);
    cout << endl;
}

int main(){
    freopen("testcase7.txt","r",stdin);
    freopen("output7.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}