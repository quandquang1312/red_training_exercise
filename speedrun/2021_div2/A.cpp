// https://codeforces.com/contest/2021/problem/A

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];

        sort(arr.begin(), arr.end(), greater<int>());

        while (arr.size() > 1) {
            int d = arr.size() - 1;
            pair<int, int> lst = {arr[d], arr[d-1]};
            int new_val = (lst.first + lst.second) / 2;
            arr.pop_back();
            arr.pop_back();
            arr.push_back(new_val);

            sort(arr.begin(), arr.end(), greater<int>());
        }

        cout << arr[0] << "\n";
    }

    return 0;
}