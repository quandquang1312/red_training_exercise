// https://atcoder.jp/contests/abc359/tasks/abc359_e

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    int height[n+1], dp[n+1] {}; 
    for (int i=0; i<n; i++) {
        cin >> height[i];
    }

    dp[0] = 1;
    int pge[n+1] {};

    stack<int> st;
    for (int i=0; i<n; i++) {
        while (!st.empty() && height[st.top()] <= height[i]) st.pop();

        if (st.empty()) pge[i] = -1;
        else pge[i] = st.top();

        st.push(i);
    }

    for (int i=1; i<=n; i++) {
        int idx = pge[i-1];
        if (idx == -1) dp[i] = (i * height[i-1]) + 1;
        else {
            int ab = dp[idx+1];
            int lw = (i - idx - 1) * height[i-1];
            dp[i] = ab + lw;
        }
    }

    for (int i=1; i<=n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;

    return 0;
}