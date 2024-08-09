// https://atcoder.jp/contests/abc362/tasks/abc362_c

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

    vector<pair<int, int>> arr(n);

    vector<int> ans(n);
    int sm_min = 0, sm_max = 0;
    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
        sm_min += arr[i].first;
        sm_max += arr[i].second;
        ans[i] = arr[i].first;
    }

    if (sm_min <= 0 && 0 <= sm_max) {
        cout << "Yes\n";
        int rm = abs(sm_min);
        for (int i=0; i<n; i++) {
            int len = abs(arr[i].second - arr[i].first);
            if (rm >= len) {
                rm -= len;
                ans[i] = ans[i] + len;
            } else {
                ans[i] += rm;
                rm = 0;
            }

            if (rm == 0) break;
        }

        for (int i=0; i<n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    } else {
        cout << "No\n";
    }

    return 0;
}