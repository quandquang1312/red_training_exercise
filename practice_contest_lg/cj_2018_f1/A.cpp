// https://codejam.lge.com/problem/16237

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;

    int boxes = 0;

    // assign 5 kg items to each box
    boxes += e;

    // group 1 kg items and 4 kg items together
    boxes += min(a, d);

    // assign the remaining 4 kg items to each box
    boxes += max(0, d - a);

    // calculate the remaining ONEs
    a = max(0, a - d);

    if (a == 0) { // there's no 1 remain, only 2 3 left
        if (b <= c) { // 2 < 3
            boxes += c; // assign 2 to 3 and the remaining 3 to each box
        } else { // 2 > 3
            boxes += c;
            b = (b - c);
            boxes += (b + 1) / 2; 
        }
    } else { // there's still 1 remain
        if (b <= c) { // 2 <= 3
            boxes += c;
            int rm_boxes_2 = (c - b);
            // cout << "boxes so far: " << rm_one << endl;
            // cout << "rm_boxes_2: " << rm_boxes_2 << endl;
            // boxes += rm_boxes_2;
            if (rm_boxes_2 * 2 >= a) {
                boxes += 0;
            } else {
                // fill up ones to the remaining
                a -= (rm_boxes_2 * 2);
                // cout << "rm one: " << rm_one << "\n";
                // fill up ones to the new boxes
                boxes += (a / 5) + (a % 5 != 0);
            }
        } else { // 2 > 3
            boxes += c;
            b = (b - c);
            int rm_boxes_1 = (b + 1) / 2;
            // cout << "boxes so far: " << boxes << "\n";
            // cout << "rm_boxes_1: " << rm_boxes_1 << "\n";
            // assign twos to new boxes
            boxes += rm_boxes_1;
            int space_left = rm_boxes_1 + (b % 2 != 0 ? 2 : 0);
            if (a <= space_left) {
                boxes += 0;
            } else {
                a -= space_left;
                boxes += (a / 5) + (a % 5 != 0);
            }
        }
    }

    cout << boxes << "\n";

    return 0;
}