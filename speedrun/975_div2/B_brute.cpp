// https://codeforces.com/contest/2019/problem/B

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MAXN 200100

int diff[MAXN];

void update(int l, int r, int vl) {
    diff[l] += vl;
    diff[r] -= vl;
}

void apply_update(int n)
{
    for (int i=0; i<=n; i++) diff[i] += diff[i-1];
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
        int n, q; cin >> n >> q;
        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];
        for (int i=0; i<n-1; i++) {
            for (int j=i+1; j<n; j++) {
                update(arr[i], arr[j], 1);
            }
        }

        apply_update(arr[n-1]);

        for (int i=0; i<q; i++) {
            int x, cnt = 0; cin >> x;
            for (int j=arr[0]; j<=arr[n-1]; j++) {
                if (diff[j] == x) cnt++;
            }

            cout << cnt << "\n";
        }
    }

    return 0;
}