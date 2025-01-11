#include <iostream>
#include <map>

template<typename K, typename V>
class interval_map {
	// friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	template<typename V_forward>
	interval_map(V_forward&& val)
	: m_valBegin(std::forward<V_forward>(val))
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	template<typename V_forward>
	void assign( K const& keyBegin, K const& keyEnd, V_forward&& val )
		requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
	{
        // std::cout << keyBegin << " - " << keyEnd << " -> " << val << "\n";

        if (!(keyBegin < keyEnd)) return;
        // if (m_map.empty()) {
        //     m_map[keyBegin] = val;
        //     m_map[keyEnd] = m_valBegin;
        //     return;
        // }

        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);

        V valBefore = m_valBegin;
        if (itBegin != m_map.begin()) {
            auto itTmp = itBegin;
            --itTmp;
            valBefore = itTmp->second;
        }

        V valAfter = m_valBegin;
        if (itEnd != m_map.begin()) {
            auto itTmp = itEnd;
            --itTmp;
            valAfter = itTmp->second;
        }

        m_map.erase(itBegin, itEnd);

        // std::cout << valBefore << " - " << valAfter << "\n";

        if (valBefore != val) m_map[keyBegin] = val;
        if (val != valAfter) m_map[keyEnd] = valAfter;

        auto it = m_map.lower_bound(keyBegin);
        if (it != m_map.begin()) {
            auto itPrev = it;
            --itPrev;
            if (itPrev->second == it->second) {
                m_map.erase(it);
            }
        } else if (it != m_map.end() && it->second == m_valBegin) {
            m_map.erase(it);
        }

        it = m_map.lower_bound(keyEnd);
        if (it != m_map.end() && it != m_map.begin()) {
            auto itPrev = it;
            --itPrev;
            if (itPrev->second == it->second) {
                m_map.erase(it);
            }
        }

        if (!m_map.empty() && m_map.begin()->second == m_valBegin) {
            m_map.erase(m_map.begin());
        }

    }

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}

    // print
    void print() {
        for (auto [k, v] : m_map)
            std::cout << " [" << k << "," << v << "] "; 
        std::cout << "\n";
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

int main() {
    // <unsigned int, char> testing
    // {
    //     interval_map<int, char> intervalMap('D');
    //     // intervalMap.print();

    //     // std::cout << intervalMap[10] << "\n";
    
    //     intervalMap.assign(0, 10, 'A');
    //     intervalMap.print();
        
    //     intervalMap.assign(5, 12, 'B');
    //     intervalMap.print();
        
    //     intervalMap.assign(12, 16, 'B');
    //     intervalMap.print();

    //     // std::cout << intervalMap[15] << "\n";

    //     for (int i=-5; i<=15; i++) {
    //         std::cout << i << ": " << intervalMap[i] << "\n";
    //     }
    // }

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
