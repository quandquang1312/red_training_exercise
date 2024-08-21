#include <bits/stdc++.h>
using namespace std;

#define OFFSET 16000
#define MAX_V  80001
#define MAX_N  45

int n, f, dp[MAX_N][MAX_V], arr[MAX_N];
bool can_neg[MAX_N], can_pos[MAX_N];

bool solve(int idx, int sm) {
    if(idx == n) return sm == f;

    if(dp[idx][sm + OFFSET] != -1) return dp[idx][sm + OFFSET];
    
    bool minus = false, add = false;
    if (sm - arr[idx] + OFFSET >= 0)  minus = solve(idx + 1,sm - arr[idx]);
    if (sm + arr[idx] + OFFSET < MAX_V) add = solve(idx + 1,sm + arr[idx]);

    can_neg[idx] |= minus;
    can_pos[idx] |= add;

    return dp[idx][sm + OFFSET] = minus | add;
}

int main() {
    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    while(cin >> n >> f){
        if (n == 0 && f == 0) break;

        memset(dp, -1, sizeof dp);
        memset(can_pos, false, sizeof can_pos);
        memset(can_neg, false, sizeof can_neg);

        for(int i=0; i<n; i++) cin >> arr[i];

        bool solvable = solve(0,0);
        if (solvable) {
            for (int i=0; i<n; i++) {
                if (can_neg[i] && can_pos[i]) cout << '?';
                else if (can_neg[i]) cout << '-';
                else cout << '+';
            }
            cout << '\n';
        } else {
            cout << '*' << '\n';
        }
    }
}