#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void slove_case(){
    string s;
    cin >> s;
    int n = s.length();
    vector<int>dp(n+1,n+1);
    dp[0] = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            bool pal = true;
            int l = j,r = i;
            while(l<r){
                if(s[l] != s[r]){
                    pal = false;
                    break;
                }
                l++;
                r--;
            }
            if(pal){
                dp[i+1] = min(dp[j]+1,dp[i+1]);
            }
        }
    }
    cout << dp[n] << endl;
}

int main(){
    if(freopen("testcase2.txt","r",stdin)==NULL) return -1;
    if(freopen("output2.txt","w",stdout)==NULL) return -1;

    int n;
    cin >> n;
    while(n--){
        slove_case();
    }
}
