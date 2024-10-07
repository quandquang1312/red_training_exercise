// https://codejam.lge.com/problem/29891

#include <bits/stdc++.h>
using namespace std;

#define int long long

int distance(int a, int b) {
    if (a * b >= 0) {
        a = abs(a);
        b = abs(b);
        return max(a,b) - min(a,b);
    } else {
        return abs(a) + abs(b);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, k; cin >> n >> k;

    vector<int> arr(n);
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    if (k == 1) {
        int sm = 0;
        for (int i=0; i<n; i++) {
            sm += abs(arr[i]) * 2;
        }

        cout << sm << endl;
    } else {
        // group
        vector<set<int>> st;
        st.push_back({arr[0]});

        for (int i=1; i<n; i++) {
            if (i != n - 1) {
                int fr = distance(arr[i-1], arr[i]);
                int ba = distance(arr[i], arr[i+1]);
                if (fr < ba && st.back().size() < k) {
                    st.back().insert(arr[i]);
                } else {
                    st.push_back({arr[i]});
                }
            } else {
                if (st.back().size() < k) {
                    st.back().insert(arr[i]);
                } else {
                    st.push_back({arr[i]});
                }
            }
        }

        int ans = 0;
        for (auto &s : st) {
            int lst = 0;
            ans += *prev(s.end());
            for (auto e : s) {
                // cout << e << " ";
                ans += (distance(e, lst));
                lst = e;
            }
            // cout << ": " << ans << '\n';
        }

        cout << ans << endl;
    }


    return 0;
}