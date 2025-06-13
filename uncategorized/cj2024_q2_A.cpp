// https://codejam.lge.com/problem/31457

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

vector<tuple<int, int, int>> ans;

void solve(int idx, int last_plus, int last_space, int bin, int sm, int p, string& str) {
    int addition = 0;
    for (int i=last_plus+1; i<=idx; i++) {
        int c = str[i] - '0';
        addition = addition * 10 + c;
    }

    if (idx >= str.size() - 1) {
        ans.push_back({sm + addition, p, bin});
        return;
    }

    // add +
    int new_sm = sm + addition;
    solve(idx + 1, idx, last_space, bin, new_sm, p + 1, str);

    // ignore
    bin = bin ^ (1 << idx);
    solve(idx + 1, last_plus, idx, bin, sm, p, str);
}

void printBin(int n, int bin) {
    for (int i=0; i<n; i++) {
        if (bin & (1 << i)) cout << "1";
        else cout << "0";
    }
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        string str; cin >> str;

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];

        int bin = (1 << (str.size() - 1)) - 1;

        ans.clear();
        solve(0, -1, -1, bin, 0, 0, str);

        auto comp = [&] (tuple<int, int, int>& t1, tuple<int, int, int>& t2) {
            auto [sm1, p1, bin1] = t1;
            auto [sm2, p2, bin2] = t2;

            if (sm1 != sm2) return sm1 < sm2;
            for (int i=0; i<str.size()-1; i++) {
                if ((bin1 & (1 << i)) != (bin2 & (1 << i))) {
                    if (bin1 & (1 << i)) return true;
                    else return false;
                }
            }
        };

        sort(ans.begin(), ans.end(), comp);

        int s_sm = 0, p_sm = 0;
        for (auto &v : arr) {
            auto [sm, p, _] = ans[v - 1];
            s_sm += sm;
            p_sm += p;
        }

        cout << s_sm << " " << p_sm << "\n";
    }

    return 0;
}