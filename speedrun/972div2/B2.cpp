#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> findNGE(int m, vector<int>& arr) {
    vector<int> nge(m);
    stack<int> st;
    for (int i=m-1; i>=0; i--) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            st.pop();
        }

        if (st.empty()) {
            nge[i] = -1;
        } else {
            nge[i] = st.top();
        }

        st.push(i);
    }

    return nge;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m, q; cin >> n >> m >> q;

        vector<int> arr(m);
        for (int i=0; i<m; i++) cin >> arr[i];
        sort(arr.begin(), arr.end());

        // vector<int> nge = findNGE(m, arr);
        // reverse(arr.begin(), arr.end());
        // vector<int> pge = findNGE(m, arr);

        // while (q--) {
        //     int x;
        // }

        while (q--) {
            int x; cin >> x;

            if (arr[0] > x) {
                cout << arr[0] - 1 << "\n";
            } else if (arr[m - 1] < x) {
                cout << n - arr[m -1] << "\n";
            } else {
                int upp = upper_bound(arr.begin(), arr.end(), x) - arr.begin();
                int low = lower_bound(arr.begin(), arr.end(), x) - arr.begin() - 1;
                cout << (arr[upp] - arr[low]) / 2 << '\n';
            }
        }
    }

    return 0;
}