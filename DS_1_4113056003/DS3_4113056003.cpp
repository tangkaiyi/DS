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
            dp[i + 1] = max(dp[i + 1], dp[j] + subint);
        }
    }
    cout << dp[len] << endl;
}

int main(){
    freopen("testcase3.txt", "r", stdin);
    freopen("output3.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        slove_case();
    }
}