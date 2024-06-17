// https://atcoder.jp/contests/abc357/tasks/abc357_d

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;
// const int MOD = 13;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    string n; cin >> n;

    int int_n = stoi(n);

    int i = 0, numb = 0;
    for (int j=0; j<int_n; j++) {
        for (i=0; i<n.size(); i++) {
            numb *= 10;
            numb += n[i] - '0';
            numb %= MOD;

            cout << n[i] << ": " << numb << endl;

            // if (numb == 0) {
            //     i += 1;
            //     cout << i << endl;
            //     break;
            // }
        }
    }

    if (i == n.size()) {

    } else {

    }


    cout << numb << endl;

    return 0;
}