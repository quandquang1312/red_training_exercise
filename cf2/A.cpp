#include <bits/stdc++.h>
using namespace std;

#define int long long

#define LOG(...) print_with_dash(#__VA_ARGS__, __VA_ARGS__)

template<typename T>
void print_with_dash(const std::string& names, T value) {
    std::cout << names << ": " << value << std::endl;
}

template<typename T, typename... Args>
void print_with_dash(const std::string& names, T value, Args... args) {
    size_t pos = names.find(',');
    std::cout << names.substr(0, pos) << ": " << value << " - ";
    print_with_dash(names.substr(pos + 1), args...);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;
        string str; cin >> str;

        vector<int> prefix_a(n + 1, 0), prefix_b(n + 1, 0);

        for (int i=0; i<n; i++) {
            if (str[i] == 'A') prefix_a[i + 1] += 1;
            else prefix_b[i + 1] += 1;

            prefix_a[i + 1] += prefix_a[i];
            prefix_b[i + 1] += prefix_b[i];
        }

        int ans = 0;
        for (int i=0; i<m; i++) {
            int s, g; cin >> s >> g;

            int l = (g + 1) / 2, r = g;
            while (l < r) {
                int md = (l + r) / 2;

                bool ch = false;
                if (s + md <= n) {
                    ch |= ((prefix_a[s + md - 1] - prefix_a[s - 1]) >= ((g + 1) / 2));
                    ch |= ((prefix_b[s + md - 1] - prefix_b[s - 1]) >= ((g + 1) / 2));
                } else {
                    int rm = md - (n - s + 1);
                    int ttl_a = (prefix_a[n] - prefix_a[s - 1]) + (prefix_a[rm]);
                    int ttl_b = (prefix_b[n] - prefix_b[s - 1]) + (prefix_b[rm]);
                    ch |= (ttl_a >= (g + 1) / 2);
                    ch |= (ttl_b >= (g + 1) / 2);
                }

                if (ch) r = md;
                else l = md + 1;
            }

            ans += l;
        }

        cout << ans << "\n";
    }

    return 0;
}