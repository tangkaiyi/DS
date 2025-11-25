#include <iostream>
#include <vector>

using namespace std;

const int MAX_VAL = 600005;
const int MAX_N = 500005;

int inorder[MAX_N];
int postorder[MAX_N];
int posMap[MAX_VAL];

void solve(int inStart, int inEnd, int postStart, int postEnd, bool &isFirst) {
    if (inStart > inEnd || postStart > postEnd) {
        return;
    }

    int rootVal = postorder[postEnd];

    if (!isFirst) {
        cout << " ";
    }
    cout << rootVal;
    isFirst = false;
    int inIndex = posMap[rootVal];
    int leftSize = inIndex - inStart;
    solve(inStart, inIndex - 1, postStart, postStart + leftSize - 1, isFirst);
    solve(inIndex + 1, inEnd, postStart + leftSize, postEnd - 1, isFirst);
}

int main() {
    freopen("testcase1.txt","r",stdin);
    freopen("output1.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            int n;
            cin >> n;

            for (int i = 0; i < n; i++) {
                cin >> inorder[i];
                posMap[inorder[i]] = i;
            }

            for (int i = 0; i < n; i++) {
                cin >> postorder[i];
            }
            bool isFirst = true;
            solve(0, n - 1, 0, n - 1, isFirst);
            cout << "\n";
        }
    }

    return 0;
}