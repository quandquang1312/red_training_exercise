#include <bits/stdc++.h>
using namespace std;

vector<vector<double>> dp;

double choose(int n, int k) {
    if (dp[n][k] > 0) return dp[n][k];
    return dp[n][k] = choose(n - 1, k - 1) + choose(n - 1, k);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        dp = vector<vector<double>>(51, vector<double>(51, -1));
        for (int i = 0; i < dp.size(); i++) {
            dp[i][0] = dp[i][i] = 1;
        }
        int n, x, y, w;
        cin >> n >> x >> y >> w;
        double weight = 0.01 * w;
        

        if (x > n / 2) {
            cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!" << endl;
        } else if (y >= (n + 1) / 2) {
            cout << "RECOUNT!" << endl;
        } else {
            int m = n - x - y;
            double a = 0;
            double allcase = pow(2, m);
            for (int i = n / 2 + 1 - x; i <= m; i++) {
                a += choose(m, i) / allcase;
            }

            if (a > weight) {
                cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!" << endl;
            } else {
                cout << "PATIENCE, EVERYONE!" << endl;
            }
        }
    }
    return 0;
}