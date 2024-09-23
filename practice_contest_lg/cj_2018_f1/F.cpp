// https://codejam.lge.com/problem/16201

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m, k;
    cin >> n >> m >> k;

    map<int, vector<int>> undamage;
    for (int i=0; i<k; i++) {
        int r, c; cin >> r >> c;
        undamage[r].push_back(c);
    }

    vector<int> ways;
    int covers = 0;
    for (auto &[r, v] : undamage) {
        v.push_back(m + 1);
        sort(v.begin(), v.end());
        int way_r = 1, lst = 0;


        for (auto &col : v) {
            int length = col - lst - 1;
            lst = col;
            int this_way = 1;
            if (length <= 1) continue;
            covers += length / 2;
            if (length % 2 != 0) {
                this_way = (length + 1) / 2;
                way_r = (way_r * this_way) % MOD;
            }
        }

        ways.push_back(way_r);
    }

    int remain_r = n - undamage.size();
    int ans_w = 1;

    covers += remain_r * (m / 2);
    if (m % 2 != 0) ans_w = ((ans_w * ((m + 1) / 2)) % MOD) % MOD;

    for (auto &e : ways) {
        ans_w = (ans_w * e) % MOD;
    }

    cout << covers << " " << ans_w << endl;

    return 0;
}