#include <map>
#include <limits>
#include <iostream>

template<class K, class V>
class interval_map {

private:
    std::map<K,V> m_map;

public:
    // Constructor associates the whole range of K with val by inserting (K_min, val) into the map
    interval_map(V const& val) {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrites previous values in this interval. Does not change values outside this interval.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        std::cout << "isnert " << keyBegin << " - " << keyEnd << " -> " << val << "\n";
        if (!(keyBegin < keyEnd)) {
            // Empty interval, do nothing
            return;
        }

        // Find the first element not less than keyBegin
        auto itLower = m_map.lower_bound(keyBegin);
        // Find the first element not less than keyEnd
        auto itUpper = m_map.lower_bound(keyEnd);

        // Determine what value precedes keyBegin
        V valBefore;
        if (itLower != m_map.begin()) {
            valBefore = std::prev(itLower)->second;
        } else {
            valBefore = m_map.begin()->second;
        }

        // Determine what value follows keyEnd
        V valAfter;
        if (itUpper != m_map.end()) {
            valAfter = itUpper->second;
        } else if (!m_map.empty()) {
            valAfter = std::prev(m_map.end())->second;
        } else {
            valAfter = valBefore;
        }

        // Erase elements in [itLower, itUpper)
        m_map.erase(itLower, itUpper);

        // Insert (keyBegin, val) if necessary
        if (valBefore != val) {
            m_map.insert_or_assign(keyBegin, val);
        }

        // Insert (keyEnd, valAfter) if necessary
        if (val != valAfter) {
            m_map.insert_or_assign(keyEnd, valAfter);
        }

        // Ensure canonicity by removing redundant keys
        // Remove keyBegin if its value is the same as previous
        auto it = m_map.find(keyBegin);
        if (it != m_map.begin() && it != m_map.end()) {
            auto itPrev = std::prev(it);
            if (itPrev->second == it->second) {
                m_map.erase(it);
            }
        }

        // Remove keyEnd if its value is the same as previous
        it = m_map.find(keyEnd);
        if (it != m_map.begin() && it != m_map.end()) {
            auto itPrev = std::prev(it);
            if (itPrev->second == it->second) {
                m_map.erase(it);
            }
        }
    }

    // Look-up of the value associated with key
    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return it->second;
        } else {
            --it;
            return it->second;
        }
    }
    
    // print
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
        interval_map<int, char> intervalMap('D');
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