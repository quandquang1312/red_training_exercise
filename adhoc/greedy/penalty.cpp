// https://vjudge.net/contest/680793#problem/K

#include <bits/stdc++.h>
using namespace std;

#define int long long
string str;

int solve(int idx, vector<int> arr) {
    if (idx >= 10) return 10;

    int player = idx % 2;

    int rm = (10 - idx + player) / 2;
    int rm_o = (10 - idx + (1 - player)) / 2;

    if (arr[player] + rm < arr[1 - player]) return idx;
    if (arr[1 - player] + rm_o < arr[player]) return idx;

    if (str[idx] == '?') {
        int c_0 = solve(idx + 1, arr);
        arr[player]++;
        int c_1 = solve(idx + 1, arr);

        return min(c_0, c_1);
    } else {
        arr[player] += (str[idx] == '1');
        return solve(idx + 1, arr);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> str;

        vector<int> arr(2, 0);
        int ans = solve(0, arr);
        cout << ans << "\n";
    }

    return 0;
}