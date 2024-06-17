#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        int ai[n+m+5], bi[n+m+5];
        vector<pair<int, int>> traceN(n+m+5);
        for (int i=0; i< (n + m + 1); i++) cin >> ai[i];
        for (int i=0; i< (n + m + 1); i++) cin >> bi[i];

        for (int i=1; i <= (n + m + 1); i++) {
            if (ai[i-1] > bi[i-1]) {
                if (traceN[i-1].first < n)
                    traceN[i].first = traceN[i-1].first + 1;
                else traceN[i].second = traceN[i-1].second + 1;
            } else {
                if (traceN[i-1].second < m)
                    traceN[i].second = traceN[i-1].second + 1;
                else traceN[i].first = traceN[i-1].first + 1;;
            }
        }
    }

    return 0;
}