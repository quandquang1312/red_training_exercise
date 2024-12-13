// https://codeforces.com/problemset/problem/1526/C1

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e18

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i=0; i<n; i++) cin >> arr[i];

    int sm = 0, ans = 0;
    for (int i=0; i<n; i++) {
        if (sm + arr[i] >= 0) {
            // cout << sm << " + " << arr[i] << "==" << sm + arr[i] << "\n";
            pq.push(arr[i]);
            sm += arr[i];
            ans += 1;
        } else {
            if (pq.empty()) continue;
            if (pq.top() < arr[i]) {
                // cout << "pq.top() " << pq.top() << " < " << arr[i] << "\n";
                sm -= pq.top();
                pq.pop();

                pq.push(arr[i]);
                sm += arr[i];
            }
        }
    }

    cout << ans << "\n";

    return 0;
}