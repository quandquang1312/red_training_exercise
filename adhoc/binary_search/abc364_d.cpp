// https://atcoder.jp/contests/abc364/tasks/abc364_d

#include <bits/stdc++.h>
using namespace std;

vector<int> arr;

bool check(int x, int b, int k) {
    auto ls = lower_bound(arr.begin(), arr.end(), b - x);
    auto gr = upper_bound(arr.begin(), arr.end(), b + x);

    return (gr - ls) >= k;  
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, q;
    cin >> n >> q;
    arr.assign(n, 0);
    for (int i=0; i<n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());

    while (q--) {
        int b, k;
        cin >> b >> k;

        int l = 0, r = 1e9;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid, b, k)) r = mid;
            else l = mid + 1;
        }

        cout << l << endl;
    }

    return 0;
}