// https://www.hackerrank.com/contests/app-b2-pretest-5/challenges/count-of-points-covered/problem

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 400010

int diff[MAXN] {}, sz, mmax = -1;
int ended[MAXN];

void update(int l, int r, int vl) {
    diff[l] += vl;
    diff[r+1] -= vl;
    ended[r]++;
}

void apply_update()
{
    for (int i=1; i<sz; i++) {
        diff[i] += diff[i-1];
        mmax = max(mmax, diff[i]);
    }
}

int32_t main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> tmp;
    vector<pair<int, int>> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
        tmp.push_back(arr[i].first);
        tmp.push_back(arr[i].second);
    }

    unordered_map<int, int> coor;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    sz = tmp.size();

    // printf("size: %lld\n", sz);

    for (int i=0; i<sz; i++) coor[tmp[i]] = i;

    for (int i=0; i<n; i++) {
        update(coor[arr[i].first], coor[arr[i].second], 1);
    }

    apply_update();
    // for (int i=0; i<sz; i++) {
    //     printf("%lld ", diff[i]);
    // } cout << endl;

    int ans[MAXN] {};
    for (int i=0; i<sz; i++) {
        ans[diff[i]] += 1;
        if (i == sz-1) break;
        if (diff[i]-ended[i] >= 0) ans[diff[i]-ended[i]] += (tmp[i+1] - tmp[i] - 1);
        // if (ended[i] == 0)
        //     printf("%lld: %lld->%lld\n", diff[i], tmp[i], tmp[i+1] - 1);
        // else {
        //     ans[diff[i]]
        // }
        // ans[diff[i]-ended[i]] += (tmp[i+1] - tmp[i]);
    }
    // printf("\n");

    for (int i=1; i<=n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");

    return 0;
}