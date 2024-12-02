#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n);
    for (auto &e : arr) cin >> e;
    
    int ans = 0;
    int j;

    map<int, int> mp;

    for (int i=0; i<n; i=j) {
        int cnt = 1, cur = 0, lastE = arr[i];
        set<int> st;
        st.insert(arr[i]);
        j = i + 1;
        mp[arr[i]] = i;
        for (; j<n; j++) {
            if (cnt % 2 == 1) {
                if (arr[j] == lastE) {
                    cur++;
                    ans = max(ans, cur);
                }
                else {
                    mp[arr[j]] = j;
                    break;
                }
            } else {
                if (st.find(arr[j]) != st.end()) {
                    ans = max(ans, cur);
                    j = mp[arr[j]] + 1;
                    break;
                } else {
                    st.insert(arr[j]);
                    lastE = arr[j];
                }
                mp[arr[j]] = j;
            }
            cnt++;
        }
    }

    cout << ans * 2 << "\n";

    return 0;
}