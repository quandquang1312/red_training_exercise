// https://open.kattis.com/problems/trainsorting

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e5;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    int arr[n];

    for (int i=0; i<n; i++) cin >> arr[i];

    vector<int> LIS(n+1, 1), LDS(n+1, 1);
    vector<int> trace1(n+1), trace2(n+1);

    trace1[0] = -1, trace2[0] = -1;
    int max_1 = -1, max_2 = -1;
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (arr[i] < arr[j]) {
                LIS[i] = max(LIS[i], LIS[j] + 1);
                trace1[i] = j;
                if (max_1 < LIS[i]) max_1 = i;
            }
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (arr[i] > arr[j]) {
                LDS[i] = max(LDS[i], LDS[j] + 1);
                trace2[i] = j;
                if (max_2 < LDS[i]) max_2 = i;
            }
        }
    }

    int ans = 1;
    int tr1 = max_1, tr2 = max_2;

    // cout << LIS[max_1] << ": " << LDS[max_2]  << endl; 

    bool f = false;
    set<int> ele;
    while (tr1 != -1 && !f) {
        if (ele.find(tr1) != ele.end()) f = true;
        ele.insert(tr1);
        tr1 = trace1[tr1];
    }

    while (tr2 != -1 && !f) {
        if (ele.find(tr2) != ele.end()) f = true;
        tr2 = trace2[tr2];
    }

    cout << (max_1 == -1 ? 0 : LIS[max_1]) + (max_2 == -1 ? 0 : LDS[max_2]) - f << endl;

    return 0;
}