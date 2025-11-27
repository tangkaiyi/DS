#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

void slove_case(){
    int n;
    bool possible = true;
    cin >> n;
    vector<int> target_order;
    for(int i=0;i<n;i++){
        int k;
        cin >> k;
        target_order.push_back(k);
    }
    stack<int> rack;
    int current = 1;
    for(int target : target_order){
        while(rack.empty() || rack.top() != target){
            if(current > n){
                possible = false;
                break;
            }
            rack.push(current);
            current++;
        }
        if(!rack.empty() && rack.top() == target){
            rack.pop();
        }
        else{
            possible = false;
            break;
        }
    }
    if(possible) cout << "Yes\n";
    else cout << "No\n";
}

int main(){
    if(freopen("testcase1.txt", "r", stdin)==NULL) return -1;
    if(freopen("output1.txt", "w", stdout)==NULL) return -1;
    int t;
    cin >> t;
    while(t--){
        slove_case();
    }
}
