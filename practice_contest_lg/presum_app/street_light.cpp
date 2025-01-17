// https://www.hackerrank.com/contests/ab-yeh-kar-ke-dikhao/challenges/kj-and-street-lights

#include <bits/stdc++.h>
using namespace std;

const int OFFSET = 2*1e5 + 10;

int diff[OFFSET * 3]; 

void update(int l, int r, int vl) {
    diff[l] += vl;
    diff[r + 1] -= vl;
}

void apply_update()
{
    for (int i=1; i<OFFSET * 2; i++) diff[i] += diff[i-1];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int m, n; cin >> m >> n;

    int end_pos = n + OFFSET;

    for (int i=0, x, r; i<m; i++) {
        cin >> x >> r;
        update(x - r + OFFSET, x + r + OFFSET, 1);
    }

    apply_update();

    int ans = 0, cur = 0;
    for (int i=OFFSET; i<=end_pos; i++) {
        if (diff[i] > 1 || diff[i] == 0) {
            cur++;
            ans = max(ans, cur);
        } else {
            cur = 0;
        }
    }

    cout << ans << "\n";

    return 0;
}