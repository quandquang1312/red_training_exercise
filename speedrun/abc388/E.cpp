// https://atcoder.jp/contests/abc388/tasks/abc388_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n + 1);
    vector<int> diff(n + 5, 0);

    for (int i=1; i<=n; i++) cin >> arr[i];

    for (int i=1; i<=n; i++) {
        // Apply update different array at i
        diff[i] += diff[i - 1];
        arr[i] += diff[i];

        // Calculate the number of stones will be used
        int stones = arr[i];
        int stones_use = min(stones, n - i);

        // Update different array
        diff[i + 1] += 1;
        diff[i + stones_use + 1] -= 1;

        // Subtract the number of stones will be used
        arr[i] -= stones_use;
        cout << arr[i] << " ";
    }

    cout << "\n";


    return 0;
}