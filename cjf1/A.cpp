#include <bits/stdc++.h>
using namespace std;

int n, presum[1030][1030], arr[1030][1030], ans = 0;

void solve(int x1, int y1, int x2, int y2) {
    if (x2 - x1 == 1) {
        int arrx1y1 = presum[x1][y1] - presum[x1-1][y1] - presum[x1][y1-1] + presum[x1-1][y1-1];
        int arrx1y2 = presum[x1][y2] - presum[x1-1][y2] - presum[x1][y2-1] + presum[x1-1][y2-1];
        int arrx2y1 = presum[x2][y1] - presum[x2-1][y1] - presum[x2][y1-1] + presum[x2-1][y1-1];
        int arrx2y2 = presum[x2][y2] - presum[x2-1][y2] - presum[x2][y2-1] + presum[x2-1][y2-1];

        int sm = arrx1y1 + arrx1y2 + arrx2y1 + arrx2y2;
        int eat = sm % 4;
        if (eat == 0) sm -= arrx1y1;
        if (eat == 1) sm -= arrx1y2;
        if (eat == 2) sm -= arrx2y1;
        if (eat == 3) sm -= arrx2y2;
        ans += sm;
    } else {
        int sm = presum[x2][y2] - presum[x1-1][y2] - presum[x2][y1-1] + presum[x1-1][y1-1];
        int eat = sm % 4;

        int mid_x = x2 / 2, mid_y = y2 / 2;

        if (eat != 0) solve(x1,y1,mid_x,mid_y);
        if (eat != 1) solve(x1,mid_y+1,mid_x,y2);
        if (eat != 2) solve(mid_x+1,y1,x2,mid_y);
        if (eat != 3) solve(mid_x+1,mid_y+1,x2,y2);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        memset(presum, 0, sizeof presum);

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                cin >> arr[i][j];
                presum[i][j] = arr[i][j] + presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1];
            }
        }

        for (int i=2; i<=n; i+=2) {
            for (int j=2; j<=n; j+=2) {
                if (i == j && __builtin_popcount(i) == 1) {
                    int q = presum[i-1][j-1] - presum[i-2][j-1] - presum[i-1][j-2] + presum[i-2][j-2];
                    int w = presum[i-1][j] - presum[i-2][j] - presum[i-1][j-1] + presum[i-2][j-1];
                    int a = presum[i][j-1] - presum[i-1][j-1] - presum[i][j-2] + presum[i-1][j-2];
                    int s = presum[i][j] - presum[i-1][j] - presum[i][j-1] + presum[i-1][j-1];

                    int sm = q + w + a + s;
                    int eat = sm % 4;

                    if (eat == 0) arr[i-1][j-1] = 0;
                    if (eat == 1) arr[i-1][j] = 0;
                    if (eat == 2) arr[i][j-1] = 0;
                    if (eat == 3) arr[i][j] = 0;
                }
            }
        }

        solve(1,1,n,n);

        cout << ans << endl;
        ans = 0;
    }

    return 0;
}