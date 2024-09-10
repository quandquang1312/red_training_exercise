//

#include <bits/stdc++.h>
using namespace std;

/*
5
1 2 2 1 1
1 2 2 2 2
2 2 1 1 1
2 2 1 1 1
2 2 2 2 2
*/

int arr[15][15];

int count_1(int x1, int y1, int x2, int y2) {
    int ans = 0;
    for (int i=x1; i<=x2; i++) {
        for (int j=y1; j<=y2; j++) {
            if (arr[i][j] == 1) {
                ans++;
            }
        }
    }

    return ans;
}

int solve(int n, pair<int, int> ch, pair<int, int> ch2) {
    int ans = 0;

    int f = ch.first, s = ch.second;
    int f2 = ch2.first, s2 = ch2.second;
    for (int i=1; i <= n; i++) {
        for (int j=1; j <= n; j++) {
            // Case 1
            pair<int, int> en = {i + s, j + f};
            if (en.first > n || en.second > n) continue;
            int c_1 = count_1(i, j, en.first, en.second);
            cout << i << "," << j << " - " << en.first << "," << en.second << ": " << c_1 << '\n';
            for (int i2=1; i2<=n; i2++) {
                if (i2 >= i && i2 <= en.first) continue;
                for (int j2=1; j2<=n; j2++) {
                    if (j2 >= j && j2 <= en.second) continue;
                    // Case 1.1
                    if (i2 + s2 > n || j2 + f2 > n) continue;
                    int c_11 = count_1(i2, j2, i2 + s2, j2 + f2);
                    // cout << "cp\n";

                    ans = max(ans, n * n - ((2 * n) - (c_1 + c_11)));
                    // Case 1.2, rotate
                    if (i2 + f2 > n || j2 + s2 > n) continue;
                    int c_12 = count_1(i2, j2, i2 + f2, j2 + s2);
                    ans = max(ans, n * n - ((2 * n) - (c_1 + c_12)));
                    // cout << "cp\n";
                }
            }

            // Case 2, rotate
            en = {i + f, j + s};
            if (en.first > n || en.second > n) continue;
            c_1 = count_1(i, j, en.first, en.second);
            for (int i2=1; i2<=n; i2++) {
                for (int j2=1; j2<=n; j2++) {
                    // Case 1.1
                    if (i2 + s2 >= i || j2 + f2 >= j) continue;
                    int c_11 = count_1(i2, j2, i2 + s2, j2 + f2);

                    ans = max(ans, n * n - ((2 * n) - (c_1 + c_11)));
                    // Case 1.2, rotate
                    if (i2 + f2 >= i || j2 + s2 >= j) continue;
                    int c_12 = count_1(i2, j2, i2 + f2, j2 + s2);
                    ans = max(ans, n * n - ((2 * n) - (c_1 + c_12)));
                    cout << "cp\n";
                }
            }
        }
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cin >> arr[i][j];
        }
    }

    // for (int i=1; i<=n; i++) {
    //     for (int j=1; j<=n; j++) {
    //         cout << arr[i][j] << " - ";
    //     }
    //     cout << '\n';
    // }

    int ans = 0;
    for (int i=0; i<n; i++) {
        ans = max(ans, solve(n, {1, i}, {1, n - i}));
        // ans = max(ans, solve(n, {2, n - i}, {2, i}));
        // break;
    }

    cout << ans << '\n';


    return 0;
}