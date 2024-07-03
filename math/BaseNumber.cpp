#include <bits/stdc++.h>
using namespace std;

#define int long long

int convertTo10(string number, int base)
{ 
    int ans = 0;
    for (int i=number.size() - 1; i>=0; i--) {
        int temp = (number[i] - '0');
        ans += temp * pow(base, number.size() - i - 1);
    }

    return ans;
}

string convert10To2(int number) {
    string ans = "";
    while (number) {
        number /= 2;
        ans.push_back((number%2) + '0');
    }

    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    string number = "132";
    int base = 8;

    

    return 0;
}