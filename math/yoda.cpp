// https://open.kattis.com/problems/yoda

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

    int n, m;
    cin >> n >> m;

    int dn = to_string(n).size();
    int dm = to_string(m).size();
    int new_n = 0, new_m = 0;
    bool eq = false;

    if (dn == dm) {
        for (int i=0; i<dn; i++) {
            if (to_string(n)[i] > to_string(m)[i]) {
                new_n = new_n * 10 + (to_string(n)[i] - '0');
            } else if (to_string(n)[i] < to_string(m)[i]) {
                new_m = new_m * 10 + (to_string(m)[i] - '0');
            } else {
                new_n = new_n * 10 + (to_string(n)[i] - '0');
                new_m = new_m * 10 + (to_string(m)[i] - '0');
                eq = true;
            }
        }
    } else {
        string pref = "";
        for (int i=0; i<abs(dn-dm); i++) pref.push_back('0');

        if (dn < dm) {
            pref.append(to_string(n));

            for (int i=0; i<dm; i++) {
                if (pref[i] > to_string(m)[i]) {
                    new_n = new_n * 10 + (pref[i] - '0');
                } else if (pref[i] < to_string(m)[i]) {
                    new_m = new_m * 10 + (to_string(m)[i] - '0');
                } else {
                    new_n = new_n * 10 + (pref[i] - '0');
                    new_m = new_m * 10 + (to_string(m)[i] - '0');
                    eq = true;
                }
            }
        } else {
            pref.append(to_string(m));

            for (int i=0; i<dn; i++) {
                if (pref[i] > to_string(n)[i]) {
                    new_m = new_m * 10 + (pref[i] - '0');
                } else if (pref[i] < to_string(n)[i]) {
                    new_n = new_n * 10 + (to_string(n)[i] - '0');
                } else {
                    new_n = new_n * 10 + (to_string(n)[i] - '0');
                    new_m = new_m * 10 + (pref[i] - '0');
                    eq = true;
                }
            }
        }
    }

    if (eq) cout << new_n << endl << new_m << endl;
    else {
        cout << (new_n == 0 ? "YODA" : to_string(new_n)) << endl;
        cout << (new_m == 0 ? "YODA" : to_string(new_m)) << endl;
    }
    return 0;
}