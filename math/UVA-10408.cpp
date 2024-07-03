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
        bool added[1010][1010];
        memset(added, 0, sizeof added);

        for (int i=1; i<=n; i++) {
            for (int j=i; j<=n; j++) {
                int g = __gcd(i, j);
                if (added[i/g][j/g] == false) {
                    seq.push_back({i/g, j/g});
                    added[i/g][j/g] = true;
                }
            }
        }

        sort(seq.begin(), seq.end(), [](pair<int, int> p1, pair<int, int> p2) {
            double l1 = p1.first*1.0 / p1.second*1.0;
            double l2 = p2.first*1.0 / p2.second*1.0;
            return (l1 < l2);
        });

        if (k-1 < seq.size())
            cout << seq[k-1].first << "/" << seq[k-1].second << endl;
        else cout << "Invalid\n";
    }

    return 0;
}