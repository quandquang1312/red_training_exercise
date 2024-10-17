// https://codejam.lge.com/problem/27362

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e13

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, k; cin >> n >> k;

        // k *= 2;

        vector<int> A(n), B(n);
        for (int i=0; i<n; i++) cin >> A[i];
        for (int i=0; i<n; i++) cin >> B[i];

        vector<int> F(n), Fpos, Fneg;
        for (int i=0; i<n; i++) {
            F[i] = A[i] - B[i];
        }
        
        for (int i=0; i<n; i++) {
            if (F[i] < 0) Fneg.push_back(-F[i]);
            else Fpos.push_back(F[i]);
        }

        sort(Fneg.begin(), Fneg.end());
        sort(Fpos.begin(), Fpos.end());

        for (auto e : Fneg)
            cout << e << " "; cout << "\n";
        for (auto e : Fpos)
            cout << e << " "; cout << "\n";


        int l = 0, r = 10, sz = Fneg.size();
        // while (l < r) {
        for (int md=0; md<=10; md++) {
            // int md = (l + r + 1) >> 1;
            // md = 0;

            int cnt = 0;
            for (int i=0; i<sz; i++) {
                int val = Fneg[i];
                // int be = lower_bound(Fpos.begin(), Fpos.end(), val - md) - Fpos.begin();
                // int ab = lower_bound(Fpos.begin(), Fpos.end(), val + md + 1) - Fpos.begin() - 1;
                // cout << val << ": " << ab << "->" << be << "\n";
                for (int j=0; j<Fpos.size(); j++) {
                    if (Fpos[j] >= val - md && Fpos[j] <= val + md) cnt++;
                }
                // cout << val << ": " << "_" << md << ": " << cnt << "\n";
            }

            cout << md << ": " << cnt << "\n";// << cnt << "\n";


            if (cnt >= k) r = md;
            else l = md + 1;
            // break;
        }

        cout << l << "\n";
    }

    return 0;
}