// https://atcoder.jp/contests/abc387/tasks/abc387_c

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

    int a, b; cin >> a >> b;

    if (a > b) swap(a, b);

    auto normalize = [](int n) -> string {
        string str = to_string(n);
        for (int i=1; i<str.size(); i++) {
            if (str[i] >= str[i-1]) {
                for (int j=i; j<str.size(); j++) {
                    str[j] = '?';
                    // if (str[i - 1] == '0') str[j] = '0';
                    // else str[j] = ((str[i - 1] - '0') - 1) + '0';
                }
                break;
            }
        }

        return str;
    };

    string l = normalize(a);
    string r = normalize(b);

    cout << "l: " << l << "\n";
    cout << "r: " << r << "\n";

    int ans = 0;
    while (l.size() <= r.size()) {
        if (l.size() < r.size()) {
            int lst_val = 0, lst_pos;
            for (int i=0; i<l.size(); i++) {
                if (l[i] != '?') lst_val = l[i], lst_pos = i;
                else break;
            }

            int d = l.size() - lst_pos - 1;
            ans += pow(lst_val, d);

            int first_digit = l[0] - '0';
            for (int i=1; i<l.size(); i++) l[i] = '?';
            l[0] = (first_digit + 1) + '0';
        } else {

        }
    }

    return 0;
}