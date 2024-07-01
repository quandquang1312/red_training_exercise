// https://codepro.lge.com/exam/19/overseas-questions-for-previous-test/quiz/13

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    string s, c;
    cin >> s >> c;

    int cur = s.size();

    for (auto &i : c) {
        if (i == 'R') {
            cur = min((int)s.size(), cur + 1);
        } else if (i == 'L') {
            cur = max(0, cur - 1);
        } else if (i == 'B') {
            if (cur == 0) continue;
            s.erase(s.begin() + (cur - 1));
            cur = max(0, cur - 1);
        } else {
            s.insert(s.begin() + cur, i);
            cur = min((int)s.size(), cur + 1); 
        }
    }

    cout << s << endl;

    return 0;
}