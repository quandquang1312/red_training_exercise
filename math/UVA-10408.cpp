// https://vjudge.net/problem/UVA-10408

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

    int n=1, k=1;
    while (cin >> n >> k) {
        vector<pair<int, int>> seq;

        for (int i=1; i<=n; i++) {
            for (int j=i+1; j<=n; j++) {
                seq.push_back({i, j});
            }
        }

        sort(seq.begin(), seq.end(), [](pair<int, int> p1, pair<int, int> p2) {
            double l1 = p1.first*1.0 / p1.second*1.0;
            double l2 = p2.first*1.0 / p2.second*1.0;
            return (l1 < l2);
        });

        cout << seq[k-1].first << "/" << seq[k-1].second << endl;
    }

    return 0;
}