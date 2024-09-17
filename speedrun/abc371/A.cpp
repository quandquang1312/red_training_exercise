#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    char ans;
    char ab, ac, bc;
    cin >> ab >> ac >> bc;

    if ((ab == '<' && ac == '>') || (ab == '>' && ac == '<')) {
        cout << "A\n";
    } else if ((ab == '<' && bc == '<') || (ab == '>' && bc == '>')) {
        cout << "B\n";
    } else {
        cout << "C\n";
    };

    return 0;
}