// https://codeforces.com/contest/5/problem/C

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    string str; cin >> str;

    int n = str.size();
    stack<int> st;
    set<int> trace;

    for (int i=0; i<n; i++) {
        if (str[i] == ')') {
            if (st.empty()) continue;
            if (str[st.top()] == '(') {
                trace.insert(st.top());
                trace.insert(i);
                st.pop();
            } else {
                while (!st.empty()) st.pop();
            }
        } else {
            st.push(i);
        }
    }

    int cur = 0, mx = 0, cnt_mx = 1;
    int last = -1;

    for (auto &e : trace) {
        if (last == -1) {
            cur = 1;
            last = e;
            continue;
        }

        if (e == last + 1) {
            cur++;
            if (cur == mx)
                cnt_mx++;
            if (cur > mx) {
                cnt_mx = 1;
                mx = cur;
            }
        } else {
            cur = 1;
        }

        last = e;
    }

    cout << mx << " " << cnt_mx << "\n";

    return 0;
}