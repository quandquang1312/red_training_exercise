// https://www.acmicpc.net/problem/3151

#include <bits/stdc++.h>
using namespace std;

#define int long long

// n2 sol
int solven2(int n, vector<int>& arr) {
    int ans = 0;
    for (int i=0; i<n && arr[i] <= 0; i++) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sm = arr[i] + arr[l] + arr[r];
            if (sm == 0) {
                int cnt_l = 0, cnt_r = 0;
                for (int j=l; j<n && arr[j] == arr[l]; j++) cnt_l++;
                for (int j=r; j>i && arr[j] == arr[r]; j--) cnt_r++;
                if (arr[l] == arr[r]) ans += (cnt_l * (cnt_l - 1)) / 2;
                else ans += cnt_r * cnt_l;
                l += cnt_l;
                r -= cnt_r;
            } else if (sm > 0) r--;
            else l++;
        }
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);

    for (int i=0; i<n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());

    int ans = solven2(n, arr);
    cout << ans << '\n';

    return 0;
}