// https://vjudge.net/problem/UVA-10922

#include <bits/stdc++.h>
using namespace std;

int ans = 0;

bool calc(string n) {
    ans++;

    int sm = 0;
    for (int i=0; i<n.size(); i++)
        sm += n[i] - '0';

    if (sm < 10) return (sm % 9 == 0);
    else return calc(to_string(sm));
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    string n;
    while (cin >> n) {
        if (n.compare("0") == 0) break;

        ans = 0;

        int ret = calc(n);

        if (ret) {
            printf("%s is a multiple of 9 and has 9-degree %d.\n",
                n.c_str(), ans);
        } else {
            printf("%s is not a multiple of 9.\n", n.c_str());
        }
    }

    return 0;
}