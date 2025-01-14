// reference: https://leetcode.com/problems/convert-a-number-to-hexadecimal/

#include <bits/stdc++.h>
using namespace std;

#define int long long

bool checkHex(const char& c) {
    return (std::isdigit(c) || \
        std::tolower(c) == 'a' || \
        std::tolower(c) == 'b' || \
        std::tolower(c) == 'c' || \
        std::tolower(c) == 'd' || \
        std::tolower(c) == 'e' || \
        std::tolower(c) == 'f');
}

int convertTo10(std::string str, int base) {
    int n = str.size();
    int pos = n - 1;
    
    int result = 0;
    
    for (int i=0; i<n; i++) {
        if (base ==  2) {
            assert(std::isdigit(str[i]) && "Invalid binary number");
            int c = str[i] - '0';
            assert((c >= 0 && c <= 1) && "Invalid binary number");
            
            result = result + (c * pow(base, pos));
        } else if (base == 8) {
            assert(std::isdigit(str[i]) && "Invalid octal number");
            int c = str[i] - '0';
            assert((c >= 0 && c <= 7) && "Invalid octal number");
            
            result = result + (c * pow(base, pos));
        } else if (base == 16) {
            assert(checkHex(str[i]) && "Invalid hexadecimal number");
           
            if (std::isdigit(str[i])) {
                int c = str[i] - '0';
                result = result + (c * pow(base, pos));
            } else {
                result = result + ((str[i] - 'a' + 10) * pow(base, pos));
            }
        } else {
            std::cout << "Not support the base";
            break;
        }
        pos--;
    }
    
    return result;
}

string convert2to16(std::string str) {
    int n = str.size();
    string rs = "";

    for (int i=n-1; i>=0; i-=4) {
        int cur = 0;
        for (int j=0; i-j>=0 && j<4; j++)
            if (str[i-j] == '1') cur |= (1 << j);

        char c = (cur < 10 ? cur + '0' : 65 + (cur - 10));
        rs.push_back(c);
    }

    reverse(rs.begin(), rs.end());

    return rs;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    cout << convert2to16("11110101100") << "\n";

    return 0;
}