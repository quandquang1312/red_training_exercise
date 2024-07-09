// https://vjudge.net/problem/UVA-11228

#include <bits/stdc++.h>
using namespace std;

// #define int long long

class UnionFind
{
private:
    vector<int> p, rank, setSize;
    int numSets;

public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        rank.assign(N, 0);
        setSize.assign(N, 1);
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
    void unionSet(int i, int j)
    {
        if (isSameSet(i, j))
            return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y])
            swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y])
            ++rank[y];
        setSize[y] += setSize[x];
        --numSets;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    for (int t=1; t<=tc; t++) {
        int n, r;
        cin >> n >> r;

        vector<pair<int, int>> arr(n);
        vector<vector<int>> adj(n);

        double distance[n][n];
        memset(distance, -1.0, sizeof distance);

        for (int i=0; i<n; i++) {
            cin >> arr[i].first >> arr[i].second;
        }

        bool visited[n] {};

        vector<vector<int>> CCs;

        for (int u=0; u<n; u++) {
            for (int v=u+1; v<n; v++) {
                int f = arr[u].first - arr[v].first;
                int s = arr[u].second - arr[v].second;

                distance[u][v] = sqrt(f*f + s*s);
                distance[v][u] = distance[u][v];
            }
        }

        queue<int> q;
        for (int i=0; i<n; i++) {
            if (visited[i]) continue;

            vector<int> cc;
            cc.push_back(i);

            visited[i] = true;
            q.push(i);

            while (!q.empty())
            {
                int u = q.front(); q.pop();

                for (int v=0; v<n; v++) {
                    if (visited[v]) continue;
                    if (distance[u][v] <= r) {
                        cc.push_back(v);
                        q.push(v);
                        visited[v] = true;
                    }
                } 
            }

            CCs.push_back(cc);
        }

        int k = CCs.size();
        double min_dist[k][k];

        vector<tuple<double, int, int>> ELs;

        for (int i=0; i<k; i++) {
            vector<int> tmp1 = CCs[i];
            for (int j=i+1; j<k; j++) {
                min_dist[i][j] = 1e9*1.0;
                vector<int> tmp2 = CCs[j];

                for (int d1=0; d1<tmp1.size(); d1++) {
                    for (int d2=0; d2<tmp2.size(); d2++) {
                        double dis = distance[tmp1[d1]][tmp2[d2]];
                        min_dist[i][j] = min(min_dist[i][j], dis);
                        min_dist[j][i] = min(min_dist[j][i], dis);
                    }
                }

                ELs.push_back({min_dist[i][j], i, j});
            }
        }

        sort(ELs.begin(), ELs.end());
        UnionFind UFs(k);
        
        double rail = 0, cnt1 = 0;
        for (auto &[w, u, v] : ELs) {
            if (UFs.isSameSet(u, v)) continue;
            rail += w;
            cnt1++;
            UFs.unionSet(u, v);

            if (cnt1 == k-1) break;
        }

        double road = 0;
        for (int cc=0; cc<CCs.size(); cc++) {
            vector<tuple<double, int, int>> EL;

            vector<int> vct = CCs[cc];
            for (int i=0; i<vct.size(); i++) {
                int u = vct[i];
                for (int j=i+1; j<vct.size(); j++) {
                    int v = vct[j];

                    EL.push_back({distance[u][v], u, v});
                }
            }

            sort(EL.begin(), EL.end());

            UnionFind UF(n);

            double mst_cost = 0.0, cnt = 0;
            for (auto &[w, u, v] : EL) {
                if (UF.isSameSet(u, v)) continue;

                mst_cost += w;
                UF.unionSet(u,v);
                cnt++;

                if (cnt == vct.size() - 1) break;
            }
            road += (mst_cost);
        }

        cout << "Case #" << t << ": " << CCs.size() << " " << round(road) << " " << round(rail) << endl;
    }

    return 0;
}