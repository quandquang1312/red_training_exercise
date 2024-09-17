// https://www.acmicpc.net/problem/31177

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define OFFSET 2000000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, k; cin >> n >> k;

    vector<int> arr(n), adjust(OFFSET * 2 + 1, 0);
    unordered_map<int, int> fre;

    int ans = 0; 
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        arr[i] += OFFSET;
        fre[arr[i]]++;
        ans = max(ans, fre[arr[i]]);
    }

    if (k == 0) {
        cout << ans << '\n';
        return 0;
    }

    for (int i=0; i<n; i++) {
        int b = arr[i];

        // if apply adding k to i-th then the value of arr[i] would not be arr[i] anymore
        // but arr[i] + k, so we have to decrease the adjust[arr[i] - k]
        // because when we consider j-th that arr[j] = arr[i] - k, we may count i-th to its answer
        // we can think that we exclude the number of x between y when we change the value of
        // y to y + k (because the x's not x anymore but x + k)
        // y x x y
        adjust[b - k] = max(0LL, adjust[b - k] - 1);

        // we increase the count of value b that adjust to b + k
        adjust[b] += 1;

        // the answer is the frequence of b + k and the number of element i-th that arr[i] = b
        // which all of it we add k to its value
        ans = max(ans, fre[b + k] + adjust[b]);
    }

    cout << ans << '\n';

    return 0;
}