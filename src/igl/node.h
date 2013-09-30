#ifndef _NODE_H_
#define _NODE_H_

#include "common/common.h"
#include "vmath/vmath.h"

struct Serializer;

struct Node {
    virtual ~Node() { }
};

template<typename T, typename U>
inline T* cast(U* ptr) {
    return static_cast<T*>(ptr);
}

template <typename T, typename U>
inline bool is(U* ptr) {
    return bool(dynamic_cast<T*>(ptr));
}

#endif
