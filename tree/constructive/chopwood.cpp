// https://open.kattis.com/problems/chopwood?tab=metadata

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n;
    cin >> n;
    vector<int> arr(n);

    map<int, int> cnt;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }

    priority_queue<int> pq;
    for (int i=1; i<=n; i++) {
        if (cnt.find(i) == cnt.end()) pq.push(-i);
    }

    bool possible = true;
    vector<int> ans;
    for (int i=0; i<n; i++) {
        if (pq.size() == 0) {
            possible = false;
            break;
        }
        int v = arr[i];
        cnt[v]--;
        int u = -pq.top();
        ans.push_back(u);
        pq.pop();
        if (cnt[v] <= 0) pq.push(-v);
    }

    if (possible == false) {
        cout << "Error\n";
    } else {
        for (auto &e : ans) {
            cout << e << '\n';
        }
    }

    return 0;
}