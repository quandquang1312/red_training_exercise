// https://open.kattis.com/problems/fibonaccicycles?tab=metadata

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int q; cin >> q;
    while (q--)
    {
        int fibrepeat[1020], k, i = 2;
        cin >> k;

        fibrepeat[0] = fibrepeat[1] = 1;
        map<int, int> visited;

        for (; i<=k+10; i++) {
            fibrepeat[i] = (fibrepeat[i-1] + fibrepeat[i-2]) % k;
            if (visited.find(fibrepeat[i]) != visited.end()) break;
            visited[fibrepeat[i]] = i;
        }

        cout << visited[fibrepeat[i]] << endl;
    }

    return 0;
}