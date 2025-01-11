#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
#include <set>

template<typename K, typename V>
class interval_map {
	// friend void IntervalMapTest();
public:
	V m_valBegin;
	std::map<K,V> m_map;
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
        if (!(keyBegin < keyEnd)) return;
        if (m_map.empty()) {
            m_map[keyBegin] = val;
            m_map[keyEnd] = m_valBegin;
            return;
        }

        auto itBegin = m_map.lower_bound(keyBegin);
        auto itEnd = m_map.lower_bound(keyEnd);

        V valB = m_valBegin;
        if (itBegin != m_map.begin()) valB = std::prev(itBegin)->second;

        V valA = m_valBegin;
        if (itEnd != m_map.begin()) valA = std::prev(itEnd)->second;

        m_map.erase(itBegin, itEnd);

        if (valB != val) m_map.insert(itEnd, {keyBegin, std::forward<V_forward>(val)});
        if (val != valA) m_map.insert(itEnd, {keyEnd, std::forward<V_forward>(valA)});

        auto it = m_map.lower_bound(keyBegin);
        if (it != m_map.begin()) {
            auto itPrev = std::prev(it);
            if (itPrev->second == it->second) {
                m_map.erase(it);
            }
        } else {
            if (it != m_map.end() && it->second == m_valBegin) {
                m_map.erase(it);
            }
        }

        it = m_map.lower_bound(keyEnd);
        if (it != m_map.end()) {
            if (it != m_map.begin()) {
                auto itPrev = std::prev(it);
                if (itPrev->second == it->second) {
                    m_map.erase(it);
                }
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

    // remove duplicate
    void remove_duplicate() {
        auto it = m_map.begin();
        V prev_val = m_valBegin;
        while (it != m_map.end()) {
            // The value should not be equal to the previous value
            if (prev_val == it->second) {
                std::cout << "Consecutive entries\n";
            }
            prev_val = it->second;
            ++it;
        } 
    }

    // print
    void print() {
        if (m_map.empty()) return;
        for (auto [k, v] : m_map)
            std::cout << " [" << k << "," << v << "] "; 
        std::cout << "\n";
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

void IntervalMapTest() {
    // std::cout << "checkpoint\n";

    using K = int;
    using V = char;

    // Initialize the interval_map with 'A' for all keys
    interval_map<K, V> imap('A');

    // Reference map for validation
    std::map<K, V> ref_map;

    // Initial range of keys for testing
    const K MIN_KEY = -100;
    const K MAX_KEY = 100;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distributions for keys and values
    std::uniform_int_distribution<K> key_dist(MIN_KEY - 20, MAX_KEY + 20);
    std::uniform_int_distribution<int> len_dist(1, 20);
    std::uniform_int_distribution<int> val_dist(0, 25); // for letters 'A' to 'Z'

    // Initialize the reference map with 'A' for all keys
    for (K k = MIN_KEY - 50; k <= MAX_KEY + 50; ++k) {
        ref_map[k] = 'A';
    }

    // Perform at least 100 random assignments
    const int NUM_TESTS = 1000;
    for (int test = 0; test < NUM_TESTS; ++test) {
        // Generate random keyBegin and length
        K keyBegin = key_dist(gen);
        K length = len_dist(gen);
        K keyEnd = keyBegin + length;

        // Ensure keyBegin < keyEnd
        if (!(keyBegin < keyEnd))
            std::swap(keyBegin, keyEnd);

        // Generate random value
        V val = 'A' + val_dist(gen);

        // Debug output
        // std::cout << "Test " << test + 1 << ": Assigning '" << val
        //           << "' to [" << keyBegin << ", " << keyEnd << ")\n";

        // Perform assignment
        imap.assign(keyBegin, keyEnd, val);

        // Update the reference map
        for (K k = keyBegin; k < keyEnd; ++k) {
            ref_map[k] = val;
        }

        // Verify correctness
        for (K k = MIN_KEY; k <= MAX_KEY; ++k) {
            V expected = ref_map[k];
            V actual = imap[k];
            assert(expected == actual && "Value mismatch between interval_map and reference map.");
        }

        // Verify canonicity
        auto it = imap.m_map.begin();
        V prev_val = imap.m_valBegin;
        while (it != imap.m_map.end()) {
            // The value should not be equal to the previous value
            assert(!(prev_val == it->second) && "Consecutive entries have the same value.");
            prev_val = it->second;
            ++it;
        }
        // First entry's value should not be equal to m_valBegin
        if (!imap.m_map.empty()) {
            assert(!(imap.m_valBegin == imap.m_map.begin()->second) &&
                   "First map entry has the same value as m_valBegin.");
        }
    }

    std::cout << "All tests passed successfully!\n";
}

template<typename K, typename V>
void IntervalMapTest_2(V initial_value, K min_key, K max_key) {
    // Initialize the interval_map with the initial value for all keys
    interval_map<K, V> imap(initial_value);

    // Reference map for validation
    std::map<K, V> ref_map;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distributions for keys and values
    std::uniform_int_distribution<K> key_dist(min_key, max_key);
    std::uniform_int_distribution<int> len_dist(1, 20);
    std::uniform_real_distribution<V> val_dist(0.0, 100.0);

    // Initialize the reference map with the initial value for all keys
    for (K k = min_key - 50; k <= max_key + 50; ++k) {
        ref_map[k] = initial_value;
    }

    // Perform at least 100 random assignments
    const int NUM_TESTS = 1000;
    for (int test = 0; test < NUM_TESTS; ++test) {
        // Generate random keyBegin and length
        K keyBegin = key_dist(gen);
        K length = len_dist(gen);
        K keyEnd = keyBegin + length;

        // Ensure keyBegin < keyEnd
        if (!(keyBegin < keyEnd))
            std::swap(keyBegin, keyEnd);

        // Generate random value
        V val = val_dist(gen);

        // Perform assignment
        imap.assign(keyBegin, keyEnd, val);

        // Update the reference map
        for (K k = keyBegin; k < keyEnd; ++k) {
            ref_map[k] = val;
        }

        // Verify correctness
        for (K k = min_key; k <= max_key; ++k) {
            V expected = ref_map[k];
            V actual = imap[k];
            assert(expected == actual && "Value mismatch between interval_map and reference map.");
        }

        // Verify canonicity
        auto it = imap.m_map.begin();
        V prev_val = imap.m_valBegin;
        while (it != imap.m_map.end()) {
            // The value should not be equal to the previous value
            assert(!(prev_val == it->second) && "Consecutive entries have the same value.");
            prev_val = it->second;
            ++it;
        }
        // First entry's value should not be equal to m_valBegin
        if (!imap.m_map.empty()) {
            assert(!(imap.m_valBegin == imap.m_map.begin()->second) &&
                   "First map entry has the same value as m_valBegin.");
        }
    }

    std::cout << "All tests passed successfully for unsigned int, double!\n";
}

// Include your interval_map implementation here

template<typename K, typename V>
void IntervalMapTest_3(V initial_value, K min_key, K max_key) {
    // Initialize the interval_map with the initial value for all keys
    interval_map<K, V> imap(initial_value);

    // Reference map for validation
    std::map<K, V> ref_map;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distributions for keys and values
    std::uniform_real_distribution<K> key_dist(min_key, max_key); // For double keys
    std::uniform_real_distribution<K> len_dist(0.1, 5.0); // Lengths from 0.1 to 5.0
    std::uniform_int_distribution<V> val_dist(0, 100); // Integer values

    // Sample a set of keys for testing
    std::set<K> sample_keys;
    const int NUM_KEYS = 1000;
    for (int i = 0; i < NUM_KEYS; ++i) {
        K k = key_dist(gen);
        sample_keys.insert(k);
    }

    // Initialize the reference map with the initial value for all sampled keys
    for (const K& k : sample_keys) {
        ref_map[k] = initial_value;
    }

    // Perform random assignments
    const int NUM_TESTS = 1000;
    for (int test = 0; test < NUM_TESTS; ++test) {
        // Generate random keyBegin and keyEnd
        K keyBegin = key_dist(gen);
        K length = len_dist(gen);
        K keyEnd = keyBegin + length;

        // Ensure keyBegin < keyEnd
        if (!(keyBegin < keyEnd))
            std::swap(keyBegin, keyEnd);

        // Generate random value
        V val = val_dist(gen);

        // Perform assignment
        imap.assign(keyBegin, keyEnd, val);

        // Update the reference map
        for (auto& [k, v] : ref_map) {
            if (keyBegin <= k && k < keyEnd) {
                v = val;
            }
        }

        // Verify correctness
        for (const auto& [k, expected] : ref_map) {
            V actual = imap[k];
            if (expected != actual) {
                std::cerr << "Mismatch at key " << k << ": expected " << expected << ", got " << actual << "\n";
            }
            assert(expected == actual && "Value mismatch between interval_map and reference map.");
        }

        // Verify canonicity
        auto it = imap.m_map.begin();
        V prev_val = imap.m_valBegin;
        while (it != imap.m_map.end()) {
            assert(!(prev_val == it->second) && "Consecutive entries have the same value.");
            prev_val = it->second;
            ++it;
        }
        if (!imap.m_map.empty()) {
            assert(!(imap.m_valBegin == imap.m_map.begin()->second) &&
                   "First map entry has the same value as m_valBegin.");
        }
    }

    std::cout << "All tests passed successfully for interval_map<double, int>!\n";
}

int main() {
    for (int i=1; i<=1000; i++) {
        std::cout << "result _ 1: " << i << ": ";
        IntervalMapTest();
    }

    for (int i=0; i<=1000; i++) {
        std::cout << "result _ 2: " << i << ": ";
        IntervalMapTest_2<unsigned int, double>(0.0, 0, 1000);
    }

    for (int i=0; i<=1000; i++) {
        std::cout << "result _ 3: " << i << ": ";
        IntervalMapTest_3<double, int>(-1, -100.0, 105.0);
    }

    // <unsigned int, char> testing
    {
        // interval_map<int, char> intervalMap('D');
        // intervalMap.print();

        // intervalMap.assign(0, 13, 'A');
        // intervalMap.print();
        
        // intervalMap.assign(5, 8, 'B');
        // intervalMap.print();
        
        // intervalMap.assign(3, 6, 'C');
        // intervalMap.print();

        // intervalMap.assign(6, 11, 'C');

        // // std::cout << intervalMap[15] << "\n";

        // for (int i=-5; i<=15; i++) {
        //     std::cout << i << ": " << intervalMap[i] << "\n";
        // }
    }
    return 0;
}
