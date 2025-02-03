// https://codeforces.com/problemset/problem/2031/D

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    int value;
    int idx;
    
    bool operator<(const Node& other) const {
        if (value == other.value)
            return idx < other.idx;
        return value < other.value;
    }
};

// From i find the largest index j where j > i && arr[j] > arr[i]
vector<int> getSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    
    set<Node> bst;
    
    for (int i=n-1; i>=0; i--) {
        auto it = bst.lower_bound({arr[i], 0});
        if (it != bst.begin()) {
            it--;
            result[i] = it->idx;
        }
        
        bst.insert({arr[i], i});
    }
    
    return result;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> arr(n);
        
        vector<int> prefixMax(n, 0);
        vector<int> suffixMin(n, 0);

        for (int i=0; i<n; i++) {
            cin >> arr[i];
            if (i) prefixMax[i] = max(prefixMax[i - 1], arr[i]);
            else prefixMax[i] = arr[i];
        }

        for (int i=n-1; i>=0; i--) {
            if (i < n - 1) suffixMin[i] = min(suffixMin[i + 1], arr[i]);
            else suffixMin[i] = arr[i];
        }

        vector<int> dp(n, 0);

        for (int i=n-1; i>=0; i--) {
            if (i == n - 1) dp[i] = prefixMax[i];
            else {
                int p = prefixMax[i];
                int s = suffixMin[i + 1];

                if (p > s) dp[i] = dp[i + 1];
                else dp[i] = prefixMax[i];
            }
        }

        for (int i=0; i<n; i++) {
            cout << dp[i] << " ";
        }

        cout << "\n";
    }

    return 0;
}