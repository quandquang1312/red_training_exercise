// https://vjudge.net/problem/UVA-11038

#include <bits/stdc++.h>
using namespace std;

#define int long long

int binpow(int a, int b) {
    if (a == 0) return 0;
    if (b == 1) return a;

    int res = 1;
    while (b) {
        if (b & 1) res = (res * a);
        a = a * a;
        b >>= 1;
    }

    return res;
}

int solve(string n) {
    int ans = 0;

    for (int i=1; i<n.size(); i++) {
        string prefix = n.substr(0, i);
        string suffix = n.substr(i+1,n.size()-i-1);

        if (suffix.empty()) {
            ans += stoi(prefix);
            continue;
        }

        int tmp_ans = 0;
        if (n[i] == '0') {
            int fir = (stoi(prefix) - 1) * binpow(10, suffix.size());
            int sec = stoi(suffix) + 1;
            tmp_ans += fir + sec; 
        } else {
            tmp_ans += stoi(prefix) * binpow(10, suffix.size());
        }

        ans += tmp_ans;
    }

    return ans + 1;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int a = 1, b = 1;
    while ((cin >> a >> b), (a != -1 && b != -1)) {
        string n = to_string(a-1), m = to_string(b);

        if (a == 0) cout << solve(m) << endl;
        else cout << solve(m) - solve(n) << "\n";
    }

    return 0;
}