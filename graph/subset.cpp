#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    int arr[n+1];
    for (int i=1; i<=n; i++) {
        cin >> arr[i];
    }

    vector<vector<int>> ss;
    for (int i=1; i < (1 << n); i++) {
        vector<int> st;
        for (int j=0; j<n; j++) {
            if ((i & (1 << j)) != 0) st.push_back(arr[j+1]);
        }
        ss.push_back(st);
    }

    for (auto &v : ss) {
        for (auto &e : v) {
            cout << e << " ";
        }
        cout << endl;
    }

    return 0;
}