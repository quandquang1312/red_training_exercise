// https://codeforces.com/contest/1975/problem/C

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
        int arr[n+1] {};
 
        for (int i=0; i<n; i++) {
            cin >> arr[i];
        }

        auto findMed = [](int a, int b, int c) {
            vector<int> arr = {a, b, c};
            sort(arr.begin(), arr.end());
            return arr[1];
        };

        int mmax = -1;
        for (int i=1; i<n-1; i++) {
            mmax = max(mmax, findMed(arr[i], arr[i-1], arr[i+1]));
        }

        if (n == 2) mmax = min(arr[0], arr[1]);
        cout << mmax << endl;
    }
 
    return 0;
}