// https://atcoder.jp/contests/abc384/tasks/abc384_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, s; cin >> n >> s;
    vector<int> arr(n * 2);

    int sm = 0;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        arr[i + n] = arr[i];
        sm += arr[i];
    }

    s = s % sm;
    n = n * 2;

    int l = 0, r = 0, cur = 0;
    bool ans = false;
    for (; r<n && !ans; r++) {
        cur += arr[r];

        while (l <= r && cur > s) {
            cur -= arr[l];
            l++;
        }

        if (cur == s) ans = true;
    }

    cout << (ans ? "Yes" : "No") << "\n";

    return 0;
}