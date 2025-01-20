#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    vector<pair<int, int>> arr(m);

    int sm = 0;

    for (int i=0; i<m; i++) cin >> arr[i].first;
    for (int i=0; i<m; i++) {
        cin >> arr[i].second;
        sm += arr[i].second;
    }

    sort(arr.begin(), arr.end());

    if (arr[0].first != 1 || sm < n) {
        cout << "-1\n";
    } else {
        bool possible = true;

        vector<int> presum(m + 1, 0); // 2 * 10^9 -> RTE
        for (int i=0; i<m; i++) {
            presum[i+1] += presum[i] + arr[i].second;
        }

        for (int i=1; i<=m && possible; i++) {
            if (presum[i] - arr[i-1].second < arr[i-1].first - 1) possible = false;
        }

        if (possible == false) {
            cout << "-1\n";
        } else {
            int ans = 0, lst = n;
            if (arr[m-1].first == n) {
                arr.pop_back();
                lst = n - 1;
            }

            // cout << "sz: " << arr.size() << '\n';
            for (int i=arr.size() - 1; i>=0; i--) {
                int len = (lst - arr[i].first);
                if (len == 0) {
                    lst = arr[i].first - 1;
                    continue;
                }

                if (len <= arr[i].second) {
                    int sm = (len * (len + 1)) / 2;
                    ans += sm;
                    if (len == arr[i].second)
                        lst = arr[i].first;
                    else lst = arr[i].first - 1;
                } else {
                    // move all xi of ai
                    Bigint len_bi(to_string(len));
                    Bigint len_1(to_string(len + 1));
                    Bigint n2("2");
                    Bigint sm = (len_bi * len_1) / n2;

                    Bigint dif_bi(to_string(len));
                    Bigint dif_1(to_string(len + 1));
                    Bigint dif = (dif_bi * dif_1) / n2;
                    int difi = (len - arr[i].second);
                    Bigint real = sm - (dif_bi * (dif_1)) / n2;
                    ans = ans + real;
                    lst -= difi;
                }
                // cout << i << ": " << ans << '\n';
            }

            ans.print();// << '\n';
        }
    }

    return 0;
}