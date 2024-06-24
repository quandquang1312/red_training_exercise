// https://codeforces.com/contest/1978/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--)
    {
        int n, k;
        cin >> n >> k;
    
        int max_k = 0;
        
        for (int i=(n % 2 ? 0 : 1); i<n; i+=2)
            max_k += i * 2;
        
        if (k > max_k || (k % 2 != 0)) {
            cout << "No\n";
            continue;
        }
        
        cout << "Yes\n";

        vector<int> ans(n+1);
        for (int i=1; i<=n; i++) ans[i] = i;

        int st = 1, en = n;
        while (k > 0) {
            int first = st, second = en;

            int x = k / 2;
            if (first + x > en) {
                second = en;
                en--;
            } else {
                second = first + x;
            }

            k -= abs(second - first) * 2;

            st++;

            ans[first] = second;
            ans[second] = first;
        }

        for (int i=1; i<=n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}