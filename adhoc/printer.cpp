// https://www.acmicpc.net/problem/1966

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, k; cin >> n >> k;
        deque<pair<int, bool>> arr;
        priority_queue<int> q;

        for (int i=0; i<n; i++) {
            int p; cin >> p;
            bool need = (i == k);
            arr.push_back({p, need});
            q.push(p);
        }

        int ans = 0;
        while (1) {
            int mmax = q.top();
            auto [p, need] = arr.front();
            arr.pop_front();

            if (p == mmax) {
                ans++;
                q.pop();

                if (need == true) break;
            } else {
                arr.push_back({p, need});
            }
        }

        cout << ans << endl;
    }


    return 0;
}