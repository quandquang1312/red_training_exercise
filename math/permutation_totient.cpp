// https://www.spoj.com/problems/TIP1/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200100

int result[MAXN];

vector<int> euler_1_n(int n)
{
    vector<int> phi(n+1);
    for (int i=0; i<=n; i++) phi[i] = i;

    for (int i=2; i<=n; i++) {
        if (phi[i] == i) {
            for (int j=i; j<=n; j+=i) {
                phi[j] -= phi[j] / i;
            }
        }
    }

    int lst = 0;
    for (int i=2; i<n; i++) {
        string stri = to_string(i), strphi = to_string(phi[i]);
        sort(stri.begin(), stri.end());
        sort(strphi.begin(), strphi.end());

        if (stri == strphi) {
            result[i] = i;
            lst = i;
        }
        else {
            result[i] = lst;
        }
    }

    // for (int i=0; i<n; i++) {
    //     if (result[i]) cout << i << ": " << result[i] << endl;
    // }

    return phi;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;

    euler_1_n(MAXN);

    while (tc--)
    {
        int n; cin >> n;

        cout << result[n] << endl;
    }

    return 0;
}

