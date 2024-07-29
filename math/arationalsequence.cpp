// https://open.kattis.com/problems/rationalsequence

#include <bits/stdc++.h>
using namespace std;

#define int long long

// the lowest common parent of p and q
// it's up to the lowest left child from p and q
// left child is where p < q
int treeUp(int p, int q, int& parentP, int& parentQ) {
    if (p < q) {
        parentP = p;
        parentQ = q - p;
        return 0;
    }

    return 1 + treeUp(p - q, q, parentP, parentQ);
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
        int k, p, q, ansp = -1, ansq = -1;
        string pq;
        cin >> k >> pq;

        int slash = pq.find('/');
        p = stoi(pq.substr(0, slash));
        q = stoi(pq.substr(slash + 1));

        if (p < q) { // left child
            // parent node: p / (q - p)
            // right child of parent: q / (q - p)
            ansp = q;
            ansq = (q - p);
        } else if (q == 1) { // right most child
            // left most child of the next height: 1 / (p + 1)
            ansp = 1;
            ansq = p + 1;
        } else { // normal right child
            int parP, parQ;
            int height = treeUp(p, q, parP, parQ);
            // cout << p << "/" << q << ": " << parP << "/" << parQ << '\n';

            // the first level dow would be the right child
            ansp = parP + parQ, ansq = parQ;
            while (height--) {
                // left most child
                ansq = (ansp + ansq);
            }
        }

        cout << k << " " << ansp << "/" << ansq << '\n';
    }

    return 0;
}