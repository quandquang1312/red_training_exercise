#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <mutex>

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int>& Map,
              std::pair<int, int> MapDimensions,
              std::vector<int>& OutPath)
{
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    int r = MapDimensions.first, c = MapDimensions.second;
    int total_cell = Map.size();

    assert(((void)"Invalid Map Dimensions", total_cell == r * c));

    std::vector<bool> visited(total_cell, false);
    std::vector<int> trace(total_cell, -1);

    auto checkValidPosition = [](int pos, int total_cell) -> bool {
        return pos >= 0 && pos < total_cell;
    };

    auto genNewPosition = [](int curr_pos, int r, int total_cell, int d) -> int {
        if (d == 0) {
            if (curr_pos % r == 0) return -1;
            return curr_pos - 1;
        }
        else if (d == 1) {
            if (curr_pos >= total_cell - r) return -1;
            return curr_pos + r;
        }
        else if (d == 2) {
            if ((curr_pos + 1) % r == 0) return -1;
            return curr_pos + 1;
        }
        else { // d == 3
            if (curr_pos < r) return -1;
            return curr_pos - r;
        }
    };

    auto convertCoor = [](std::pair<int, int> p, int r) -> int {
        int rs = p.first;
        rs = rs + r * p.second;
        return rs;
    };

    int st = convertCoor(Start, r);
    int en = convertCoor(Target, r);

    if (st == en) return true;

    std::queue<int> q;
    q.push(st);
    visited[st] = true;

    int timer = 0, ans = -1;
    while (q.size() > 0 && ans == -1) {
        int sz = q.size();
        while (sz-- && ans == -1) {
            int curr_pos = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int new_pos = genNewPosition(curr_pos, r, total_cell, d);
                if (!checkValidPosition(new_pos, total_cell)) continue;
                if (Map[new_pos] == 0 || visited[new_pos]) continue;

                trace[new_pos] = curr_pos;
                if (new_pos == en) {
                    ans = timer;
                    break;
                }

                q.push(new_pos);
                visited[new_pos] = true;
            }
        }

        timer++;
    }

    if (ans == -1) return false;

    OutPath.clear();
    int curr = en;

    while (curr != st) {
        OutPath.push_back(curr);
        curr = trace[curr];
    }

    std::reverse(OutPath.begin(), OutPath.end());

    return true;
}

int32_t main() {
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif
    {
        std::vector<int> Map = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
        std::vector<int> OutPath;
        bool test = FindPath({0, 0}, {1, 2}, Map, {4, 3}, OutPath);

        if (test == false) {
            std::cout << "False\n";
        } else {
            for (auto &e : OutPath) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        std::vector<int> Map = {0, 0, 1, 0, 1, 1, 1, 0, 1};
        std::vector<int> OutPath;
        bool test = FindPath({2, 0}, {0, 2}, Map, {3, 3}, OutPath);

        if (test == false) {
            std::cout << "False\n";
        } else {
            for (auto &e : OutPath) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        std::vector<int> Map = {1};
        std::vector<int> OutPath;
        bool test = FindPath({0, 0}, {0, 0}, Map, {1, 1}, OutPath);

        if (test == false) {
            std::cout << "False\n";
        } else {
            for (auto &e : OutPath) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}