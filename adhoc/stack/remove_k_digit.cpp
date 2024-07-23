// https://leetcode.com/problems/remove-k-digits/

#include <bits/stdc++.h>
using namespace std;

#define int long long

class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();

        stack<int> st;
        for (int i=0; i<n; i++) {
            int val = num[i] - '0';
            while (!st.empty() && st.top() > val && k > 0) {
                st.pop();
                k--;
            }

            st.push(val);
        }

        while (k--) st.pop();

        string ans = "";
        while (!st.empty()) {
            ans.push_back(st.top() + '0');
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        int i=0;
        while (ans[i] == '0') {
            ans.erase(ans.begin());
        }

        return (ans.size() == 0 ? "0" : ans);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        string num;
        int k;

        cin >> num;
        cin >> k;

        Solution sol;
        string ans = sol.removeKdigits(num, k);
        cout << ans << endl;
    }

    return 0;
}