// https://vjudge.net/problem/UVA-443

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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    set<int> st;

    int MAXN = 100;

    for (int i=0; i<=100 && st.size() < MAXN; i++) {
        for (int j=0; j<=100 && st.size() < MAXN; j++) {
            for (int d=0; d<=100 && st.size() < MAXN; d++) {
                for (int k=0; k<=100 && st.size() < MAXN; k++) {
                    int ans = binpow(2, i) * binpow(3, j) * binpow(5, d) * binpow(7, k);
                    // cout << ans << endl;
                    if (ans <= 2000000000LL && ans >= 0LL) st.insert(ans);
                }
            }
        }
    }

    vector<int> precal;

    for (auto e : st) {
        // cout << e << endl;
        precal.push_back(e);
    }

    cout << precal.size() << endl;
    sort(precal.begin(), precal.end());
    // cout << precal[1] << endl;
    int n = 1;
    while (cin >> n) {
        if (n == 0) break;
        int ans = precal[n-1];
        string suffix = "th";
        if (n % 10 == 1) suffix = "st";
        else if (n % 10 == 2) suffix = "nd";
        else if (n % 10 == 3) suffix = "rd";
        printf("The %d %s humble number is %d.\n", n, suffix.c_str(), precal[n-1]);
    }

    return 0;
}