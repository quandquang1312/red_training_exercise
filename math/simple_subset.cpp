// https://vjudge.net/problem/UVA-496

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    stringstream sin;
    string line;

    while (getline(cin, line))
    {
        vector<int> A, B;
        int num;
        sin.clear();
        sin << line;
        while (sin >> num) A.push_back(num);

        getline(cin, line);
        sin.clear();
        sin << line;
        while (sin >> num) B.push_back(num);

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        int found = 0;
        for (auto &e : A)
            if (find(B.begin(), B.end(), e) != B.end())
                found++;

        if (A.size() == B.size()) {
            if (found == A.size()) cout << "1. A equals B\n";
            else if (found == 0) cout << "2. A and B are disjoint\n";
            else cout << "3. I'm confused!\n";
        } else if (A.size() < B.size()) {
            if (found == A.size()) cout << "4. A is a proper subset of B\n";
            else if (found == 0) cout << "5. A and B are disjoint\n";
            else cout << "6. I'm confused!\n";
        } else {
            found = 0;
            for (auto &e : B)
                if (find(A.begin(), A.end(), e) != A.end())
                    found++;

            if (found == B.size()) cout << "7. B is a proper subset of A\n";
            else if (found == 0) cout << "8. A and B are disjoint\n";
            else cout << "9. I'm confused!\n";
        }
    }

    return 0;
}