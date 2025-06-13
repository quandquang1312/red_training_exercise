#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> arr(n);

        int m_max = -1;
        set<int> st;

        for (int i=0; i<n; i++) {
            cin >> arr[i];
            m_max = max(m_max, arr[i]);
            st.insert(arr[i]);
        }

        if (st.size() == 1) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for (int i=0; i<n; i++) {
                if (arr[i] == m_max) cout << "1 ";
                else cout << "2 ";
            }
            cout << "\n";
        }
    }

    return 0;
}