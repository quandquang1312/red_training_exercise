#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector<pair<int, int>> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
        if (arr[i].first < arr[i].second) swap(arr[i].first, arr[i].second);
    }

    auto comp = [&] (const pair<int, int>& p1, const pair<int, int>& p2) {
        if (p1.first == p2.first) return p1.second < p2.second;
        return p1.first < p2.first;
    };

    sort(arr.begin(), arr.end(), comp);

    multiset<pair<int, int>, decltype(comp)> mset(comp);

    for (int i=n-1; i>=0; i--) {
        if (!mset.size()) {
            mset.insert({arr[i].first, arr[i].second});
        } else {
            auto it = mset.lower_bound({arr[i].first, arr[i].second});
            if (it != mset.end()) {
                if (arr[i].second <= it->second) mset.erase(it);
            }
            mset.insert({arr[i].first, arr[i].second});
        }

        // cout << "======\n";
        // for (auto &e : mset) {
        //     cout << e.first << " - " << e.second << "\n";
        // }
    }

    cout << mset.size() << "\n";

    return 0;
}