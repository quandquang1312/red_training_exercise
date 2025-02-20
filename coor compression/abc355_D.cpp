// https://atcoder.jp/contests/abc355/tasks/abc355_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

class FenwickTree {
private:
    std::vector<long long> BIT1, BIT2;

    void update(std::vector<long long> &BIT, int index, long long value) {
        while (index < BIT.size()) {
            BIT[index] += value;
            index += index & (-index);
        }
    }

    long long query(const std::vector<long long> &BIT, int index) {
        long long sum = 0;
        while (index > 0) {
            sum += BIT[index];
            index -= index & (-index);
        }
        return sum;
    }

public:
    FenwickTree(int size) : BIT1(size + 1, 0), BIT2(size + 1, 0) {}

    void rangeUpdate(int left, int right, long long value) {
        update(BIT1, left, value);
        update(BIT1, right + 1, -value);
        update(BIT2, left, value * (left - 1));
        update(BIT2, right + 1, -value * right);
    }

    long long prefixSum(int index) {
        return query(BIT1, index) * index - query(BIT2, index);
    }

    long long query(int left, int right) {
        return prefixSum(right) - prefixSum(left - 1);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<pair<int, int>> arr(n);
    vector<int> tmp;

    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
        tmp.push_back(arr[i].first);
        tmp.push_back(arr[i].second);
    }

    unordered_map<int, int> coor;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

    for (int i=0; i<tmp.size(); i++) {
        coor[tmp[i]] = i+1;
    }

    FenwickTree ft(tmp.size() + 1);
    for (int i=0; i<n; i++) {
        ft.rangeUpdate(coor[arr[i].first], coor[arr[i].second], 1);
    }

    sort(arr.begin(), arr.end(), [](pair<int, int> p1, pair<int, int> p2){
        return p1.second < p2.second;
    });

    int ans = 0LL;
    for (int i=0; i<arr.size(); i++) {
        ans += ft.query(coor[arr[i].second], coor[arr[i].second]) - 1;
        ft.rangeUpdate(coor[arr[i].first], coor[arr[i].second], -1);
    }

    cout << ans << endl;

    return 0;
}