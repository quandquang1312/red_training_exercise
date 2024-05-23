// https://codeforces.com/contest/1919/problem/C

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        int arr[n] {};

        for (int i=0; i<n; i++) cin >> arr[i];

        vector<int> a, b;
        b.push_back(arr[0]);
        a.push_back(INF);
        for (int i=1; i<n; i++) {
            if (a.back() > b.back()) swap(a,b);

            if (a.back() == arr[i]) a.push_back(arr[i]);
            else if (b.back() == arr[i]) b.push_back(arr[i]);
            else if (a.back() > arr[i] && arr[i] > b.back())
                a.push_back(arr[i]);
            else // arr[i] > a.back() && arr[i] > b.back()
                b.push_back(arr[i]);
        }

        int ans = 0;
        for (size_t i=1; i<a.size(); i++)  ans += (a[i-1] < a[i]);
        for (size_t i=1; i<b.size(); i++)  ans += (b[i-1] < b[i]);

        cout << ans << endl;
    }

    return 0;
}