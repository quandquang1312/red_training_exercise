#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../ou.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<char>> grid(n + 1, vector<char>(n + 1)), ans;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> grid[i][j];
        }
    }

    ans = grid;

    for(int i = 1; i <= n/2; i++){
        int j = n+1-i;
        for(int x = i; x <= j; x++){
            for(int y = i; y <= j; y++){
                ans[y][n+1-x] = grid[x][y];
            }
        }

        grid = ans;

        // for(int i = 1; i <= n; i++){a
        //     for(int j = 1; j <= n; j++){
        //         cout << ans[i][j];
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << grid[i][j];
        }
        cout << "\n";
    }

    return 0;
}