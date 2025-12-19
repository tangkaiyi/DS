#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve_case(){
    string s;
    cin >> s;
    int len = s.length();
    vector<long long>dp(len+1,0);
    for(int i=0;i<len;i++){
        for(int j=0;j<=i;j++){
            string subs = s.substr(j,i-j+1);
            int subint = 0;
            if(!subs.empty() && !(subs[0] == '0' && subs.length() != 1)){
                try{
                    subint = stoi(subs);
                }
                catch(...){
                }
            }
            dp[i+1] = max(dp[i+1],dp[j]+subint);
        }
    }
    cout << dp[len] << endl;
}

int main(){
    freopen("testcase2.txt","r",stdin);
    freopen("output2.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        solve_case();
    }
    return 0;
}