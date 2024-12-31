#include <iostream>
#include <algorithm>
#include <limits>
#include <map>

using namespace std;

template<typename K, typename V>
class IntervalMap {
    std::map<K, V> m_map;
public:
    // Initialize the IntervalMap with the default value from -lowest bound is default_value
    IntervalMap(V const& val) {
        m_map.insert(m_map.begin(), {std::numeric_limits<K>::lowest(), val});
    }

    // Assign value V from K to the next key in the std::map (key being ordered)
    void assign(const K& keyBegin, const K& keyEnd, const V& val) {
        if (!(keyBegin < keyEnd)) {
            return;
        }

        // no need to try to add the same value to the end
        if ((--m_map.upper_bound(keyEnd))->second == val) {
            return;
        }

        auto beginLowerBound = m_map.lower_bound(keyBegin);
        auto endLowerBound = m_map.lower_bound(keyEnd);
        auto calculatedKeyBegin = keyBegin;
        bool partial = false;

        std::pair<K,V> additionalElement = *std::prev(m_map.end());

        if (additionalElement.first < keyEnd) {
            additionalElement.first = keyEnd;
        }

        auto eraseEnd = endLowerBound;

        if (keyEnd < eraseEnd->first) {
            additionalElement = std::pair(keyEnd, std::prev(endLowerBound)->second);
            partial = true;
        }

        if (beginLowerBound != m_map.end()) {
            if (eraseEnd != m_map.end() && eraseEnd->second == val && !partial) {
                ++eraseEnd;
            }

            m_map.erase(beginLowerBound, eraseEnd);
        }

        m_map.insert(std::pair(calculatedKeyBegin, val));

        if (!(additionalElement.second == val)) {
            m_map.insert(additionalElement);
        }
    }

    const V& operator[](const K& key) const {
        return (--m_map.upper_bound(key))->second;
    }

    void print() {
        for (auto [k, v] : m_map)
            std::cout << " [" << k << "," << v << "] "; 
        std::cout << "\n";
    }
};

int main() {
    // <int, std::string> testing
    {
        // IntervalMap<int, std::string> intervalMap("DEFAULT");
        // intervalMap.assign(3, 7, "APPLE");
        // intervalMap.assign(7, 10, "BANANA");

        // for (int i=-10; i<=20; i++) {
        //     std::cout << i << ": " << intervalMap[i] << "\n";
        // }
    }

    // <float, std::string> testing
    {
        // IntervalMap<float, std::string> intervalMap("FLOAT_DEFAULT");
        // intervalMap.assign(-1.0f, 3.0f, "FLOAT_APPLE");
        // intervalMap.assign(1.0f, 2.3f, "FLOAT_BANANA");

        // for (float i=-1.5f; i<=3.0f; i+=0.1f) {
        //     std::cout << i << ": " << intervalMap[i] << "\n";
        // }
    }

    // <unsigned int, char> testing
    {
        IntervalMap<int, char> intervalMap('A');
        intervalMap.print();
    
        intervalMap.assign(0, 10, 'A');
        intervalMap.print();
        
        intervalMap.assign(5, 8, 'B');
        intervalMap.print();
        
        intervalMap.assign(3, 6, 'C');
        intervalMap.print();

        // std::cout << intervalMap[15] << "\n";

        for (int i=1; i<=10; i++) {
            std::cout << i << ": " << intervalMap[i] << "\n";
        }
    }


    return 0;
}