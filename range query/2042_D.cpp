// https://codeforces.com/problemset/problem/2042/D

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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<pair<int, int>> arr(n);
        for (int i=0; i<n; i++) {
            cin >> arr[i].first >> arr[i].second;
        }

        vector<int> order(n);
        vector<bool> isvalid(n, true);

        iota(order.begin(), order.end(), 0);

        // sort to check valid
        sort(order.begin(), order.end(), [&](int i, int j) {
            if (arr[i].first == arr[j].first) return arr[i].second < arr[j].second;
            return arr[i].first < arr[j].first;
        });

        for (int i=0; i<n-1; i++) {
            int idx = order[i];
            int nxt = order[i + 1];
            if (arr[idx].first == arr[nxt].first && arr[idx].second == arr[nxt].second) {
                isvalid[idx] = false;
                isvalid[nxt] = false;
            }
        }

        // left to right by start

        sort(order.begin(), order.end(), [&](int i, int j) {
            if (arr[i].first == arr[j].first) return arr[i].second > arr[j].second;
            return arr[i].first < arr[j].first;
        });

        set<int> endpoints;

        vector<int> ans(n, 0);

        for (int i=0; i<n; i++) {
            int idx = order[i];

            // cout << arr[idx].first << " - " << arr[idx].second << "\n"; 
            if (!endpoints.empty()) {
                auto iter = endpoints.lower_bound(arr[idx].second);
                if (iter != endpoints.end()) {
                    ans[idx] += *iter - arr[idx].second;
                } 
            }

            endpoints.insert(arr[idx].second);
        }

        // right to left by end

        sort(order.begin(), order.end(), [&](int i, int j) {
            if (arr[i].second == arr[j].second) return arr[i].first < arr[j].first;
            return arr[i].second > arr[j].second;
        });

        set<int> startpoints;

        for (int i=0; i<n; i++) {
            int idx = order[i];

            if (!startpoints.empty()) {
                auto iter = startpoints.lower_bound(-arr[idx].first);
                if (iter != startpoints.end()) {
                    ans[idx] += max(0LL, abs(arr[idx].first + (*iter)));
                }
            }

            startpoints.insert(-arr[idx].first);
        }

        for (int i=0; i<n; i++) {
            cout << (isvalid[i] ? ans[i] : 0) << "\n";
        }
    }

    return 0;
}