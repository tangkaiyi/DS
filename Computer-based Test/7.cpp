#include <iostream>

using namespace std;

int inorder[500005];
int postorder[500005];
int inorder_pos[600005];

void preorder(int inStart,int inEnd,int postStart,int postEnd){
    if(inStart>inEnd || postStart>postEnd) return;

    int root = postorder[postEnd];
    int inIndex = inorder_pos[root];
    int leftsize = inIndex - inStart;
    cout << root << " ";

    preorder(inStart,inIndex-1,postStart,postStart+leftsize-1);
    preorder(inIndex+1,inEnd,postStart+leftsize,postEnd-1);
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
    preorder(0,n-1,0,n-1);
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