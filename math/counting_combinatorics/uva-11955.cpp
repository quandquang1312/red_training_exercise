// https://vjudge.net/problem/UVA-11955

#include <bits/stdc++.h>
using namespace std;

#define int long long
string a, b;
int k, n, m;

void inp() {
    string tmp, ret;
    cin >> ret;
    a.clear() , b.clear() , tmp.clear();
    int i ,len = ret.size() ;
    for(i = 1; ret[i] != '+'; i++ ) a += ret[i];
    for(i++; ret[i] != ')'; i++ ) b += ret[i];
    for(i += 2; i < len; i++ ) tmp += ret[i];
    k = stoi(tmp);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc, t = 1;
    cin >> tc;

    // Pascal Triangle
    int64_t c[60 + 1][60 + 1];
    memset(c, 0, sizeof c);
    for (int i = 0; i <= 60; i++) { c[i][0] = 1; }
    for (int i = 1; i <= 60; i++) {
        for (int j = 1; j <= 60; j++) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }

    // k = 3;
    // for (int i=1; i<=k; i++) {
    //     cout << i << ": " << c[i][k] << "-" << c[k][i] << "\n";
    // }

    while (tc--) {
        inp();

        string ans = "";
        vector<string> tmp_ans;
        int ka = k, kb = 0;
        for (int i=0; i<=k; i++) {
            string xi = to_string(c[k][i]);
            if (xi.compare("0") == 0 || xi.compare("1") == 0) xi = "";

            string ai = (ka != 0 ? (a + '^' + to_string(ka)) : "");
            if (ka == 1) ai = a;

            string bi = (kb != 0 ? (b + '^' + to_string(kb)) : "");
            if (kb == 1) bi = b;
            
            
            if (xi.size()) tmp_ans.push_back(xi);
            if (ai.size()) tmp_ans.push_back(ai);
            if (bi.size()) tmp_ans.push_back(bi);
            ka--;
            kb++;
        }
        // cout << tmp_ans.size() << '\n';
        cout << "Case " << t << ": " << tmp_ans[0]; 
        for (int i=1; i<tmp_ans.size()-2; i+=3) {
            // cout << i << ": " << tmp_ans[i] << '\n';
            // cout << i+1 << ": " << tmp_ans[i+1] << '\n';
            // cout << i+2 << ": " << tmp_ans[i+2] << '\n';
            cout << "+" << tmp_ans[i] << "*" << tmp_ans[i+1] << "*" << tmp_ans[i+2];
        }
        cout << "+" << tmp_ans[tmp_ans.size()-1] << '\n';
        t++;
    }

    return 0;
}