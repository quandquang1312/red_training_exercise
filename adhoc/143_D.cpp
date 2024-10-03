// https://codeforces.com/problemset/problem/143/D

#include <bits/stdc++.h>
using namespace std;

// Maximum knights to place where each knight can not be attacked in a n x m chess board
int maxHorses(int n, int m) {
    if (n > m) swap(n, m);

    if (n == 1) return m; 
    if (n == 2) return m / 4 * 4 + min(2, m % 4) * 2; 
    if (n == 3 && m == 3) return 5;

    return (n * m + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;
    int ans = maxHorses(n, m);
    cout << ans << endl;

    return 0;
}
