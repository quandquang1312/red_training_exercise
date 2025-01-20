// https://atcoder.jp/contests/abc389/tasks/abc389_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int sqr(int a) { return a * a; }

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int r; cin >> r;
    double r2 = 4.0 * r * r;

    int ans = 4 * (r - 1) + 1; // the center cross
    int ret = 0;
    
    auto isIn = [&] (int i, int j, double r2) -> bool {
        // check the square is in r 
        // i + 0.5: the right - top point of the square
        // j + 0.5: the right - bottom point of the square
        // (i + 0.5)^2 + (j + 0.5)^2 <= r
        // but we multiple by 4 to make it integer
        // (2*i + 1)^2 + (2*j + 1)^2 <= 4*r
        double dist = sqr(2 * i + 1) + sqr(2 * j + 1);
        return dist <= r2;
    };
    
    // the larger i, the smaller j
    for (int i=1, j = r; i<r; i++) {
        while (j > 0 && !isIn(i, j, r2)) j--;
        ret += j;
    }

    ret = ret * 4; // 4 quarters
    cout << ans + ret << "\n";

    return 0;
}