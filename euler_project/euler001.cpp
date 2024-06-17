#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        n--;
        int p3 = n / 3;
        int p5 = n / 5;
        int p15 = n / 15;

        int ans3 = 3*((p3*(p3+1))/2);
        int ans5 = 5*((p5*(p5+1))/2);
        int ans15 = 15*((p15*(p15+1))/2);

        // int tmpans3 = 0, tmpans5 = 0, tmpans15 = 0;
        // for (int i=0; i<n; i++) {
        //     if (i%3 == 0) tmpans3 += i;
        //     if (i%5 == 0) tmpans5 += i;
        //     if (i%15 == 0) tmpans15 += i;
        // }

        // cout << ans3 << " " << ans5 << " " << ans15 << endl;
        // cout << tmpans3 << " " << tmpans5 << " " << tmpans15 << endl;
        cout << (ans3 + ans5 - ans15) << endl;
        // cout << (tmpans3 + tmpans5 - tmpans15) << endl;
    }

    return 0;
}