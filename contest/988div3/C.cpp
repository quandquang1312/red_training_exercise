#include <bits/stdc++.h>
using namespace std;

#define int long long

bool isPrime(int x) {
    if (x <= 1) return false;
    if (x == 2 || x == 3) return true;

    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0) return false;
    for (int i=4; i*i<=x; i++)
        if (x % i == 0) return false;
    return true;
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
        int n; cin >> n;

        if (n <= 4) {
            cout << "-1\n";
            continue;
        }

        vector<int> ans;
        int last_odd = 5, start_even = 4;
        for (int i=1; i<=n; i+=2) {
            if (i == last_odd) continue;
            ans.push_back(i);
        }

        ans.push_back(last_odd);
        ans.push_back(start_even);

        for (int i=2; i<=n; i+=2) {
            if (i == start_even) continue;
            ans.push_back(i);
        }
    
        for (auto &e : ans) {
            cout << e << " ";
        } cout << "\n";
    }

    return 0;
}