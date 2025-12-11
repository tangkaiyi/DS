#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void solve_case(){
    int n;
    cin >> n;
    vector<int> v;
    stack<int> st;
    for(int i=0;i<n;i++){
        int k;  
        cin >> k;
        v.push_back(k);
    }
    int current = 1;
    while(current){
    
    }
}

int main(){
    freopen("testcase1.txt","r",stdin);
    freopen("output1.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }           
    return 0;
}