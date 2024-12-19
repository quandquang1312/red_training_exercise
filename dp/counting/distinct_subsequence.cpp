// https://leetcode.com/problems/distinct-subsequences/description/?envType=problem-list-v2&envId=dynamic-programming

#include <bits/stdc++.h>
using namespace std;

#define int long long

class Solution {
public:
    static const int MAX_CHAR = 26;
    const char ch[MAX_CHAR] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                                'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                                'u', 'v', 'w', 'x', 'y', 'z'};

    string normalize(char c, int cnt) {
        string rs = "";
        rs.push_back(c);

        string cnt_str = to_string(cnt);
        while (5 > (rs.size() + cnt_str.size()))
            rs.push_back('0');

        rs.append(cnt_str);

        return rs;
    }

    int numDistinct(string s, string t) {
        cout << s << " | " << t << "\n";
        int n = s.size();
        int m = t.size();

        map<string, vector<string>> graph;

        int cnt_char[MAX_CHAR] {};
        vector<vector<string>> keys(MAX_CHAR); 

        string lastStr = normalize(t[0], 0);
        for (int i=1; i<m; i++) {
            int u = t[i] - 'a';

            int idx_u = cnt_char[u];

            string str_u = normalize(t[i], idx_u);

            graph[str_u].push_back(lastStr);
            keys[idx_u].push_back(str_u);

            cnt_char[u]++;

            lastStr = str_u;
        }

        for (auto &e : keys) sort(e.rbegin(), e.rend());

        for (auto &e : keys) {
            for (auto &k : e) {
                cout << k << "\n";
            }
        }

        for (auto &[u, v] : graph) {
            cout << u << ": \n";
            for (auto &e : v) {
                cout << "\t" << e << "\n";
            }
        }

        unordered_map<string, int> dp;

        for (int i=0; i<n; i++) {
            int u = s[i] - 'a';

            string str_u = normalize(u + 'a', 0);
            dp[str_u]++;
            cout << "dp " << ch[u] << " " << 0 << " ++\n";
            for (auto &key_u : keys[u]) {
                for (auto &v_idx : graph[key_u]) {
                    dp[key_u] += dp[v_idx];
                    cout << "dp " << key_u << " += " << "dp " << v_idx << "\n"; 
                }
            }

            cout << "=====\n";
        }

        return dp[lastStr]; 
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../ou.txt", "w", stdout);
    #endif

    string s = "rabbbit", t = "rabbit";
    Solution sol;
    int ans = sol.numDistinct(s, t);

    cout << ans << "\n";

    return 0;
}