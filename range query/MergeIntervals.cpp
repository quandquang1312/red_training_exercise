#include <bits/stdc++.h>
using namespace std;

#define int long long

void mergeIntervals(vector<pair<int, int>> intervals)
{
    sort(intervals.begin(), intervals.end());

    vector<pair<int, int>> st;
    st.push_back(intervals[0]);

    for (int i=1; i<intervals.size(); i++) {
        auto current = intervals[i];
        auto& _top   = st.back();

        if (current.first <= _top.second) {
            _top.second = max(_top.second, current.second);
        } else {
            st.push_back(intervals[i]);
        }
    }

    for (auto &e : st) {
        cout << e.first << " " << e.second << endl;
    }
}

int32_t main() {
    
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<pair<int, int>> intervals(n);

    for (int i=0; i<n; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    mergeIntervals(intervals);

    return 0;
}