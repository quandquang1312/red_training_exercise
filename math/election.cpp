#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int tc; cin >> tc;
    while (tc--) {
        int n, v1, v2, w;
        cin >> n >> v1 >> v2 >> w;

        int remain = n - v1 - v2;
        int ans = 0;
        for (int i=0; i<=remain; i++) {
            if ((v1 + i) * 2 > n) ans++;
        }

        if ((ans * 100) / (remain + 1) > w) printf("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!\n");
        else if (ans == 0) printf("RECOUNT!\n");
        else printf("PATIENCE, EVERYONE!\n");
    }

    return 0;
}