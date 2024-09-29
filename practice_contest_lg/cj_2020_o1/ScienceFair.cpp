// https://codejam.lge.com/problem/18767

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 10010
const int INF = 1e5;

int N = 12;
vector<vector<int>> adj, capacity, take;

// Maximum Flow
int bfs(int s, int t, vector<int>& parent, tuple<int, int, int>& fl) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<tuple<int, int, int>> q;
    q.push({s, INF, -1});

    while (!q.empty()) {
        auto [cur, flow, p] = q.front();
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) {
                    fl = {p, cur, new_flow};
                    return new_flow;
                }
                q.push({next, new_flow, cur});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, vector<tuple<int, int, int>>& sol) {
    int flow = 0;
    vector<int> parent(N);
    int new_flow;

    sol.clear();
    tuple<int, int, int> ans;

    while (new_flow = bfs(s, t, parent, ans)) {
        flow += new_flow;
        int cur = t;

        sol.push_back(ans);

        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            take[prev][cur] += new_flow;
            take[cur][prev] -= new_flow;
            cur = prev;
        }
    }

    return flow;
}

void addEdge(int x, vector<int> vct) {
    for (auto &e : vct) {
        adj[x].push_back(e);
        adj[e].push_back(x);
        capacity[x][e] = INF;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        adj.clear();
        adj.assign(N, vector<int>());
        capacity.assign(N, vector<int>(N, 0));
        take.assign(N, vector<int>(N, 0));

        // wrapper for 3 gym
        for (int i=1; i<=3; i++) {
            adj[0].push_back(i);
            adj[i].push_back(0);
            cin >> capacity[0][i];
        }

        // wrapper for the gym to the sets of volunteers
        addEdge(1, {4, 7, 8, 10});
        addEdge(2, {5, 7, 9, 10});
        addEdge(3, {6, 8, 9, 10});

        // wrapper for 7 sets of volunteer to the sink
        int sk = N - 1;
        for (int i=4; i<=10; i++) {
            adj[i].push_back(sk);
            adj[sk].push_back(i);
        }

        // add input capacity
        vector<vector<int>> cnt(n + 1);
        for (int i=1; i<=3; i++) {
            int len; cin >> len;
            while (len--) {
                int x; cin >> x;
                cnt[x].push_back(i);
            }
        }

        int A = 0, B = 0, C = 0, AB = 0, AC = 0, BC = 0, ABC = 0;
        vector<vector<int>> sol(11);
        for (int i=1; i<=n; i++) {
            if (cnt[i].size() == 1) {
                if (cnt[i][0] == 1) A++;
                else if (cnt[i][0] == 2) B++;
                else C++;

                sol[cnt[i][0] + 3].push_back(i);
            } else if (cnt[i].size() == 2) {
                sort(cnt[i].begin(), cnt[i].end());
                if (cnt[i][0] == 1 && cnt[i][1] == 2) { sol[7].push_back(i), AB++; }
                else if(cnt[i][0] == 1 && cnt[i][1] == 3) { sol[8].push_back(i), AC++; }
                else { sol[9].push_back(i), BC++; }
            } else if (cnt[i].size() == 3) {
                sol[10].push_back(i);
                ABC++;
            }
        }

        vector<int> tosk = {A, B, C, AB, AC, BC, ABC};
        for (int i=0; i<tosk.size(); i++) {
            capacity[i + 4][sk] += tosk[i];
        }

        vector<tuple<int, int, int>> trace;
        int ans = maxflow(0, sk, trace);

        cout << ans << endl;
        vector<vector<int>> idx(N, vector<int>(N, 0));
        for (auto &e : trace) {
            auto [gym, st, quant] = e;
            char g_ch = (gym == 1 ? 'A' : (gym == 2 ? 'B' : 'C'));
            for (int j=0; j<quant; j++) {
                cout << sol[st][idx[st][sk]] << " " << g_ch << "\n";
                idx[st][sk]++;
            }
        }

    }

    return 0;
}