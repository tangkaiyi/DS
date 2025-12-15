#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#define MAX_INT 2147483647

using namespace std;

void slove_case(){
    string s;
    cin >> s;
    int len = s.length();
    vector<long long> dp(len + 1, 0);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= i; j++) {
            string subs = s.substr(j, i - j + 1);
            if (subs.empty() || (subs[0] == '0' && subs.length() > 1)) continue;
            int subint = 0;
            try {
                subint = stoi(subs);
            } catch (...) {
                continue;
            }
            if (subint > MAX_INT) continue;
            dp[i + 1] = max(dp[i + 1], dp[j] + subint); //當前值與到j最大值(dp[j])加上新切割比大小
        }
    }
    cout << dp[len] << endl;
}

int main(){
    if(freopen("testcase2.txt", "r", stdin)==NULL) return -1;
    if(freopen("output2.txt", "w", stdout)==NULL) return -1;
    int t;
    cin >> t;
    while(t--){
        slove_case();
    }
}
