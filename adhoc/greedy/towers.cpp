// https://cses.fi/problemset/task/1073

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    multiset<int> st;
    st.insert(arr[0]);

    for (int i=1; i<n; i++) {
        auto it = st.upper_bound(arr[i]);
        if (it != st.end()) st.erase(it);

        st.insert(arr[i]);
    }

    cout << st.size() << "\n";

    return 0;
}