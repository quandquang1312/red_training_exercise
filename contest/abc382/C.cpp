#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e13;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    vector<int> A(n), B(m);
    vector<pair<int, int>> rB(m);
    for (int i=0; i<n; i++) cin >> A[i];
    for (int i=0; i<m; i++) {
        cin >> B[i];
        rB[i] = {B[i], i};
    }

    sort(rB.begin(), rB.end());
    sort(B.begin(), B.end());

    vector<int> ans(m, -1);
    int lastB = m;
    for (int i=0; i<n; i++) {
        int pos = lower_bound(B.begin(), B.begin() + lastB, A[i]) - B.begin();
        if (pos == lastB) continue;
        for (int j=pos; j<lastB; j++) {
            ans[rB[j].second] = i + 1;
        }
        if (pos == 0) break;
        lastB = min(lastB, pos);
    }

    for (int i=0; i<m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}