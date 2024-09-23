// https://codejam.lge.com/problem/16238

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 1005

vector<int> arr;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    arr.assign(n, 0);
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }
    
    // if we are at the i-th day
    // we can only eat the cell that has the lambs  greater than -ith
    // otherwise it will reduce to 0
    // if we have three cell a, b, c, (all three greater than 3)
    // then no matter what order we eat, it will be the same
    // and equal to (a + b + c) - (1 + 2)
    // (1 is the loss for the second cell we eat)
    // (2 is the loss for the third cell we eat)
    // generally, 
    // (a1 + a2 + a3 + ... + ak) - (1 + 2 + 3 + ... + k)
    sort(arr.begin(), arr.end(), greater<>());

    int sm = 0, cnt = 0;
    for (int i=0; i<n; i++) {
        if (arr[i] < cnt + 1) break;
        cnt += 1;
        sm += arr[i];
    }

    sm = sm - (cnt * (cnt - 1)) / 2;
    cout << sm << endl;

    return 0;
}