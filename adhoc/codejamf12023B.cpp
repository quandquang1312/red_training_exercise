// https://codejam.lge.com/problem/24432

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e12
int n, m, k, alice[25], bob[25];
set<int> a_pos, b_pos;

void choose(int arr[], int sz, int type)
{
    for (int i=0; i < (1 << sz); i++) {
        int cnt = __builtin_popcount(i);
        if (cnt == k) {
            int sm = 0;
            for (int j=0; j<sz; j++)
                if ((i & (1 << j))) sm += arr[j];
            if (type == 1) a_pos.insert(sm);
            else b_pos.insert(sm);
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m >> k;
        a_pos.clear();
        b_pos.clear();

        for (int i=0; i<n; i++) cin >> alice[i];
        for (int i=0; i<m; i++) cin >> bob[i];

        int mmin = INF, mmax = -1;

        choose(alice, n, 1);
        choose(bob, m, 2);

        vector<int> a_vect(a_pos.begin(), a_pos.end());
        vector<int> b_vect(b_pos.begin(), b_pos.end());

        for (int i=0; i<a_vect.size(); i++) {
            int fl = lower_bound(b_vect.begin(), b_vect.end(), a_vect[i]) - b_vect.begin();
            int fu = upper_bound(b_vect.begin(), b_vect.end(), a_vect[i]) - b_vect.begin();
            
            if (fl < b_vect.size()) mmin = min(mmin, abs(a_vect[i] - b_vect[fl]));
            if (fu < b_vect.size()) mmin = min(mmin, abs(a_vect[i] - b_vect[fu]));
            if (fl + 1 < b_vect.size())  mmin = min(mmin, (abs(a_vect[i] - b_vect[fl+1])));
            if (fl - 1 >= 0) mmin = min(mmin, (abs(a_vect[i] - b_vect[fl-1])));
            if (fu + 1 < b_vect.size())  mmin = min(mmin, (abs(a_vect[i] - b_vect[fu+1])));
            if (fu - 1 >= 0) mmin = min(mmin, (abs(a_vect[i] - b_vect[fu-1])));
        }

        mmax = max(abs(a_vect[0] - b_vect[0]), abs(a_vect[0] - b_vect[b_vect.size()-1]));
        mmax = max(mmax, max(abs(a_vect[a_pos.size()-1] - b_vect[0]), abs(a_vect[a_vect.size()-1] - b_vect[b_pos.size()-1])));

        cout << max(0LL, mmin) << " " << mmax << endl;
    }
    return 0;
}