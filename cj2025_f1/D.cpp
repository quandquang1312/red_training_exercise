#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e16;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<pair<int, int>> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
        if (arr[i].first < arr[i].second) swap(arr[i].first, arr[i].second);
    }

    auto comp = [&] (pair<int, int>& p1, pair<int, int>& p2) {
        if (p1.first == p2.first) return p1.second < p2.second;
        return p1.first < p2.first;
    };

    sort(arr.rbegin(), arr.rend(), comp);

    vector<int> v;
    for (int i=0; i<n; i++) {
        int p = lower_bound(v.begin(), v.end(), arr[i].second) - v.begin();
        if (p == v.size()) v.push_back(arr[i].second);
        else v[p] = arr[i].second;
    }

    cout << v.size() << "\n";

    return 0;
}