// https://codeforces.com/contest/1975/problem/B

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
 
    int tc; cin >> tc;
    while (tc--)
    {
        int n; cin >> n;
        vector<int> arr;
 
        bool found_1s = false;
        for (int i=0; i<n; i++) {
            int x; cin >> x;
            if (x != 1) arr.push_back(x);
            else found_1s = true;
        }

        if (found_1s) {
            cout << "Yes\n";
            continue;
        }

        n = arr.size();
        sort(arr.begin(), arr.end());

        int running_gcd_1 = arr[0];
        int running_gcd_2 = -1;

        int ans = true;
        for (int i=1; i<n; i++) {
            if (arr[i] == running_gcd_1 || arr[i] == running_gcd_2) continue;

            if (arr[i] % running_gcd_1 == 0) {
                running_gcd_1 = __gcd(running_gcd_1, arr[i]);
            } else {
                if (running_gcd_2 == -1) running_gcd_2 = arr[i];
                else running_gcd_2 = __gcd(running_gcd_2, arr[i]);

                if (running_gcd_2 == 1) {
                    ans = false;
                    break;
                }
            }
        }

        if (!ans) {
            cout << "No\n";
            continue;
        }

        if (running_gcd_2 == -1) {
            cout << "Yes\n";
            continue;
        }

        ans = true;
        int pos_1 = -1, pos_2 = -1;
        auto ptr_pos_1 = lower_bound(arr.begin(), arr.end(), running_gcd_1);
        auto ptr_pos_2 = lower_bound(arr.begin(), arr.end(), running_gcd_2);

        if (ptr_pos_1 != arr.end()) pos_1 = ptr_pos_1 - arr.begin();
        if (pos_1 == -1 || arr[pos_1] != running_gcd_1) ans = false;

        if (ptr_pos_2 != arr.end()) pos_2 = ptr_pos_2 - arr.begin();
        if (pos_2 == -1 || arr[pos_2] != running_gcd_2) ans = false;

        cout << (ans ? "Yes\n" : "No\n");
    }

    return 0;
}