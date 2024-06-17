// https://codeforces.com/contest/1975/problem/A
 
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif
 
    int tc; cin >> tc;
    while (tc--)
    {
        int n; cin >> n;
        int arr[n+1] {};
 
        vector<pair<int, int>> seg;
        for (int i=0; i<n; i++) cin >> arr[i];
 
        int lastEle = arr[0];
        seg.push_back({lastEle, -1});
        for (int i=1; i<n; i++) {
            if (arr[i-1] > arr[i]) {
                seg.back().second = arr[i-1];
                seg.push_back({arr[i], -1});
            }
        }
 
        if (seg.back().second == -1) seg.back().second = arr[n-1];
 
        if (seg.size() > 2) {
            cout << "No\n";
            continue;
        } else if (seg.size() == 1) {
            cout << "Yes\n";
            continue;
        } else {
            sort(seg.begin(), seg.end(), [](pair<int, int> p1, pair<int, int> p2) {
                return p1.second < p2.second;
            });

            if (seg[0].second > seg[1].first && seg[0].first < seg[1].second) cout << "No\n";
            else cout << "Yes\n";
        }
    }
 
    return 0;
}