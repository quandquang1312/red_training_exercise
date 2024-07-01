// https://leetcode.com/problems/factorial-trailing-zeroes/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    pair<int, int> primeFactors(int n)
    {
        int f2 = 0, f5 = 0;

        while (n % 2 == 0) {
            f2++;
            n /= 2;
        }

        while (n % 5 == 0) {
            f5++;
            n /= 5;
        }

        return {f2, f5};
    }

    int trailingZeroes(int n) {

        int f2 = 0, f5 = 0;
        for (int i=2; i<=n; i++) {
            pair<int, int> r = primeFactors(i);
            f2 += r.first;
            f5 += r.second;
        }
        
        int req = min(f2, f5);

        return req;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    Solution sol;
    cout << sol.trailingZeroes(101) << endl;


    return 0;
}