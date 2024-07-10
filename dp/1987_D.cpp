// https://codeforces.com/contest/1987/problem/D#

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
        int n; cin >> n;
        int arr[n];

        vector<pair<int, int>> freq;
        vector<int> cnt(n+1, 0);
        for (int i=0; i<n; i++) {
            cin >> arr[i];
            cnt[arr[i]]++;
        }
        sort(arr, arr+n);
        
        for (int i=1; i<=n; i++) {
            if (cnt[i] != 0)
                freq.push_back({i, cnt[i]});
        }

        sort(freq.begin(), freq.end(), [](pair<int, int> p1, pair<int, int> p2) {
            if (p1.second == p2.second) return p1.first > p2.first;
            return p1.second < p2.second;
        });

        vector<int> A;
        for (int i=0; i<n; i++) {
            if (A.empty() || A.back() != arr[i])
                A.push_back(arr[i]);
        }

        int ans = A.size();
        for (int i=0; i<A.size(); i++) {
            // cout << freq[i+1].first << " " << A[i] << "\n";
            if (freq[i+1].first < A[i]) {
                ans = i + 1;
                break;
            }
        }

        // cout << "\nans: " << ans << endl;

        // for (auto &[idx, f] : freq) {
        //     cout << idx << ": " << f << endl;
        // }
    }

    return 0;
}