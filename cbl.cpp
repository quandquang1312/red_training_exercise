#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> arr = {10, 14, 19, 19, 27, 31, 33};
    sort(arr.begin(), arr.end());

    auto find19 = lower_bound(arr.begin(), arr.end(), 19);
    auto find21 = lower_bound(arr.begin(), arr.end(), 21);

    std::cout << "Equal or greater than 19: " << *find19 << " at " << (find19 - arr.begin()) << "\n";
    std::cout << "Equal or greater than 21: " << *find21 << " at " << (find21 - arr.begin()) << "\n";

    return 0;
}