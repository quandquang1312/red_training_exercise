#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
    string str; cin >> str;
    int n = str.size();
    
    unordered_map<char, vector<int>> mp;
    
    for (int i=0; i<n; i++) {
        mp[str[i]].push_back(i);
    }
    
    int ans = 0;
    for (auto &[_, e] : mp) {
        if (e.size() <= 1) continue;
        if (e.size() == 2) {
            ans += e[e.size() - 1] - e[0] - 1;
            continue;
        }
        
        int sm = 0;
        for (int i=1; i<e.size(); i++) {
            sm += (e[i] - e[i-1]) * i;
            ans += (sm - i);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}