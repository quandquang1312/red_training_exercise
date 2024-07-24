#include <iostream>
#include <complex>
#include <vector>

using namespace std;

vector<bool> visited;

bool kuhn(int u, const vector<vector<int>> &adj, vector<int> &RightMatch, vector<int> &LeftMatch) {
    if (visited[u]) return false;
    visited[u] = true;
    for (auto &v : adj[u]) {
        if (LeftMatch[v] == -1 || (kuhn(LeftMatch[v], adj, RightMatch, LeftMatch))) {
            LeftMatch[v] = u;
            RightMatch[u] = v;
            return true;
        }
    }
    return false;
}

void solve(int N, int M, const vector<vector<int>> &adj)
{
    vector<int> RightMatch(N, -1), LeftMatch(M, -1);
    for (int i = 0; i < N; i++)
    {
        if (RightMatch[i] != -1) continue;
        visited.assign(200, false);
        kuhn(i, adj, RightMatch, LeftMatch);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) if (RightMatch[i] == -1) ans++;

    cout << ans << endl;
}

int main()
{
    int N, M, S, V;
    double x, y;

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    while (cin >> N >> M >> S >> V)
    {
        vector<complex<double>> gophers(N), holes(M);
        for (int i = 0; i < N; i++)
        {
            cin >> x >> y;
            gophers[i] = {x, y};
        }

        for (int i = 0; i < M; i++)
        {
            cin >> x >> y;
            holes[i] = {x, y};
        }

        vector<vector<int>> adj(N);
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < M; v++) {
                if (abs(gophers[u] - holes[v]) <= S * V) adj[u].push_back(v);
            }
        }

        solve(N, M, adj);
    }
}