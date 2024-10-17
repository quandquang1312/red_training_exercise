#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e13;
const int MOD = 1e9 + 7;

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

class FenwickTree {
public:
    FenwickTree(int n) {
        this->n = n;
        ft.assign(n, 0);
    }

    FenwickTree(vector<int> arr) : FenwickTree(arr.size()) {
        for (int i=0; i<arr.size(); i++)
            add(i, arr[i]);
    }

    int query(int l, int r) {
        return sum(r) - sum(l-1);
    }

    void add(int idx, int vl) {
        for (; idx < n; idx = idx | (idx + 1))
            ft[idx] += vl;
    }

private:
    vector<int> ft;
    int n;

private:
    int g(int i) { return i & (i + 1); }
    int sum(int i) {
        int rs = 0;
        while (i >= 0) {
            rs += ft[i];
            i = g(i) - 1;
        }
        return rs;
    }
};

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

        vector<int> arr(n);
        for (auto &e : arr) cin >> e;

        FenwickTree ft(arr);

        vector<int> t(m), L(m), R(m);

        for (int i=0; i<m; i++) cin >> t[i];
        for (int i=0; i<m; i++) cin >> L[i];
        for (int i=0; i<m; i++) cin >> R[i];

        int ori = 0, sign = 0;

        for (int i=0; i<m; i++) {
            if (t[i] == 1) {
                ori = ori + L[i];
                if (ori >= n) ori = (ori - n) % n;
            } else if (t[i] == 2) {
                ori = ori - L[i];
                if (ori < 0) ori = (n + ori) % n;
            } else if (t[i] == 3) {
                sign = 1 - sign;
            } else if (t[i] == 4) {
                if (sign == 0) {
                    for (int j=ori; j < ori + L[i]; j++) {
                        ft.add((j % n), R[i]);
                    }
                } else {
                    for (int j=ori; j > ori - L[i]; j--) {
                        if (j < 0) {
                            ft.add((n + j) % n, R[i]);
                        } else {
                            ft.add((j % n), R[i]);
                        }
                    }
                }
            } else {
                int ans = 0;
                if (sign == 0) {
                    if (ori + L[i] >= n) {
                        ans = ft.query(ori, n - 1);
                        ans += ft.query(0, L[i] - (n - ori) - 1);
                    } else {
                        ans = ft.query(ori, ori + L[i] - 1);
                    }
                } else {
                    if (L[i] <= ori) {
                        ans += ft.query(ori - L[i], ori);
                    } else {
                        ans += ft.query(0, L[i]);
                    }
                }
                cout << ans << " ";
            }
        }

        cout << "\n";

    }

    return 0;
}