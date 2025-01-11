/*
// Task Description
interval_map<K,V> is a data structure that efficiently associates intervals of keys of type K with values of type V. 
Your task is to implement the assign member function of this data structure, which is outlined below.

interval_map<K, V> is implemented on top of std::map. In case you are not entirely sure which functions std::map provides, 
what they do and which guarantees they provide, we provide an excerpt of the C++ standard here: 

Each key-value-pair (k,v) in the std::map means that the value v is associated with the interval from k (including) to the next key (excluding) in the std::map.

Example: the std::map (0,'A'), (3,'B'), (5,'A') represents the mapping

0 -> 'A'
1 -> 'A'
2 -> 'A'
3 -> 'B'
4 -> 'B'
5 -> 'A'
6 -> 'A'
7 -> 'A'
 ... all the way to numeric_limits<int>::max()

The representation in the std::map must be canonical, that is, consecutive map entries must not have the same value: 
..., (0,'A'), (3,'A'), ... is not allowed. Initially, the whole range of K is associated with a given initial value, 
passed to the constructor of the interval_map<K,V> data structure.

Key type K:
besides being copyable and assignable, is less-than comparable via operator<
is bounded below, with the lowest value being std::numeric_limits<K>::lowest() does not implement any other operations,
in particular no equality comparison or arithmetic operators

Value type V:
besides being copyable and assignable, is equality-comparable via operator== does not implement any other operations
*/

// REFERENCE

// https://github.com/minhdv82/kengolib/blob/51b70f25e41e61a9016324e81500c19752f0cfaf/range.h
// https://github.com/projected1/interval-map
// https://stackoverflow.com/questions/54068482/where-exactly-does-my-code-not-adhere-to-the-specification-of-the-key-and-value/61629286#61629286

// CHATGPT-Prompt
/*
Given the requirements of implementing the interval_map class (initial template as below),
you should implement based on the following criterities:
- Type requirements: You must adhere to the specification of the key and value type given above
- Correctnect: You program should produce a working interval_map with the behavior described above. In particular, pay attention to the validity of
iterators. It is illegal to dereference end iterators. Consider using a checking STL implementation such as the one shipped with Visual C++ or GCC
- Canonicity: The representation in m_map must be canonicity
- Running time: Image your implementation is part of a library, so it should be big-O optimal. In addition:
      - Do not make big-O more operations on K and V than neccesary because you do not know how fast operations on K/V are; remember that
      constructions, destructions and assignments are operations as well
      - Do not make more than one operation of amortized O(log N), in constrast to O(1), running time where N is the number of elements in m_map
      - Otherwise favor simplicity over minor speed improvements
*/

template<class K, class V>
class interval_map {

private:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val) into the map
    interval_map( V const& val) {
        // INSERT YOUR SOLUTION HERE
    }

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        // INSERT YOUR SOLUTION HERE
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        // INSERT YOUR SOLUTION HERE
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

int main() {
    // IntervalMapTest();

    return 0;
}