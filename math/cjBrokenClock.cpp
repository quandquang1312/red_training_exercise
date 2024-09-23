// https://codejam.lge.com/problem/21981

#include <bits/stdc++.h>
using namespace std;

#define OFFSET (60 * 60 * 24)
#define modulo(x) ((((long long) x) + OFFSET) % OFFSET)

vector<pair<int,int>> normalize(const vector<pair<int, int>> &arr) {
    map<int,int> m;
    for (auto &p : arr) {
        int a = modulo(p.first % OFFSET);
        int b = modulo(p.second % OFFSET);
        if (!m.count(a)) m[a] = b;
        if (m[a] != b) return {};
    }

    vector<pair<int,int> > ans;
    for (auto &p : m)
        ans.push_back(p);
    return ans;
}

static inline int f(int x, int a, int b) {
    return modulo(a * x + b);
}

bool intersect(int t, const vector<pair<int, int>>& line) {
    int n = line.size();
    if (n < 2) return false;

    int init = f(t, line[0].first, line[0].second);
    for (int i=1; i<n; i++) {
        int val = f(t, line[0].first, line[0].second);
        if (val != init) return false;
    }

    return true;
}

int solve(const vector<pair<int, int>>& arr) {
    vector<pair<int, int>> norm_lines = normalize(arr);

    if (norm_lines.empty()) return 0;
    if (norm_lines.size() == 1)  return arr.size() > 1 ? OFFSET : 0;

    int ans = 0;
    for (int sec=0; sec<OFFSET; sec++) {
        if (intersect(sec, norm_lines)) ans++;
    }

    return ans;
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
        int n; cin >> n;

        vector<pair<int, int>> arr(n);
        for (int i=0; i<n; i++) {
            string str; cin >> str;
            int h = (str[0] - '0') * 10 + (str[1] - '0');
            int m = (str[3] - '0') * 10 + (str[4] - '0');
            int s = (str[6] - '0') * 10 + (str[7] - '0');
            arr[i].second = h * 60 * 60 + m * 60 + s;
        }

        for (int i=0; i<n; i++) cin >> arr[i].first;

        int ans = solve(arr);
        cout << ans << '\n';
    }

    return 0;
}