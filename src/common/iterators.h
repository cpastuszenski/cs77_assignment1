#ifndef _ITERATORS_H_
#define _ITERATORS_H_

template<typename T>
struct counting_iterator {
    T current;
    counting_iterator(const T& value) : current(value) { }
    T& operator*() { return current; }
    counting_iterator<T>& operator++() { ++current; return *this; }
    bool operator!=(const counting_iterator<T>& other) { return current != other.current; }
};

template<typename T>
struct counting_container {
    T min, max;
    
    counting_container(const T& min, const T& max) : min(min), max(max) { }
    
    counting_iterator<T> begin() { return counting_iterator<T>(min); }
    counting_iterator<T> end() { return counting_iterator<T>(max); }
};

inline counting_container<int> range(int max) { return counting_container<int>(0,max); }
inline counting_container<int> range(int min, int max) { return counting_container<int>(min,max); }
    
#endif