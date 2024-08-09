// https://codeforces.com/problemset/problem/1117/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

bool check(int d, const pair<int, int>& target, const string& str) {
    int n = str.size();
    
    int xc = 0,yc = 0, i = 0;
    for (; i<n; i++) {
        if (str[i] == 'U') xc += 1;
        else if (str[i] == 'D') xc -= 1;
        else if (str[i] == 'L') yc -= 1;
        else if (str[i] == 'R') yc += 1;

            
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int xi, yi, xt, yt;
    cin >> xi >> yi >> xt >> yt;
    string str; cin >> str;

    pair<int, int> target {xt - xi, yt - yi};
    if (target.first == 0 && target.second == 0) {
        cout << "0\n";
    } else {

    }


    return 0;
}