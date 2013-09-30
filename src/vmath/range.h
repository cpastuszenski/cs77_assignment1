#ifndef _RANGE_H_
#define _RANGE_H_

#include "vec.h"
#include <array>
using std::array;

template<typename T>
struct range1 {
    T min, max;

    explicit range1() : min(+1), max(-1) { }
    explicit range1(const T& min, const T& max) : min(min), max(max) { }

    static int size() { return 2; }

    T* begin() { return &min; }
    T* end() { return (&min)+2; }
    const T* begin() const { return &min; }
    const T* end() const { return (&min)+2; }

    T* data() { return &min; }

    T* raw_data() { return &min; }
    static int raw_size() { return 2; }
 };


using range1f = range1<float>;
using range1d = range1<double>;
using range1i = range1<int>;

template<typename T> inline bool isvalid(const range1<T>& a) { return min(a.min,a.max) == a.min; }

template<typename T> inline T size(const range1<T>& a) { return (a.max-a.min); }
template<typename T> inline T center(const range1<T>& a) { return (a.max+a.min)/2; }

template<typename T> inline range1<T> runion(const range1<T>& a, const T& b) { if(not isvalid(a)) return range1<T>(b,b); return range1<T>(min(a.min,b),max(a.max,b)); }
template<typename T> inline range1<T> runion(const range1<T>& a, const range1<T>& b) { if(not isvalid(a)) return b; if(not isvalid(b)) return a; return range1<T>(min(a.min,b.min),max(a.max,b.max)); }

template<typename T> inline range1<T> rscale(const range1<T>& a, const T& b) { return range1<T>(center(a)-size(a)*b/2,center(a)+size(a)*b/2); }

template<typename T>
struct range2 {
    vec2<T> min, max;

    explicit range2() : min(+1,+1), max(-1,-1) { }
    explicit range2(const vec2<T>& min, const vec2<T>& max) : min(min), max(max) { }

    static int size() { return 2; }

    vec2<T>* begin() { return &min; }
    vec2<T>* end() { return (&min)+2; }
    const vec2<T>* begin() const { return &min; }
    const vec2<T>* end() const { return (&min)+2; }

    vec2<T>* data() { return &min; }

    T* raw_data() { return min.raw_data(); }
    static int raw_size() { return 2*vec2<T>::raw_size(); }
 };


using range2f = range2<float>;
using range2d = range2<double>;
using range2i = range2<int>;

template<typename T> inline bool isvalid(const range2<T>& a) { return min(a.min,a.max) == a.min; }

template<typename T> inline vec2<T> size(const range2<T>& a) { return (a.max-a.min); }
template<typename T> inline vec2<T> center(const range2<T>& a) { return (a.max+a.min)/2; }

template<typename T> inline range2<T> runion(const range2<T>& a, const vec2<T>& b) { if(not isvalid(a)) return range2<T>(b,b); return range2<T>(min(a.min,b),max(a.max,b)); }
template<typename T> inline range2<T> runion(const range2<T>& a, const range2<T>& b) { if(not isvalid(a)) return b; if(not isvalid(b)) return a; return range2<T>(min(a.min,b.min),max(a.max,b.max)); }

template<typename T> inline range2<T> rscale(const range2<T>& a, const T& b) { return range2<T>(center(a)-size(a)*b/2,center(a)+size(a)*b/2); }

template<typename T>
struct range3 {
    vec3<T> min, max;

    explicit range3() : min(+1,+1,+1), max(-1,-1,-1) { }
    explicit range3(const vec3<T>& min, const vec3<T>& max) : min(min), max(max) { }

    static int size() { return 2; }

    vec3<T>* begin() { return &min; }
    vec3<T>* end() { return (&min)+2; }
    const vec3<T>* begin() const { return &min; }
    const vec3<T>* end() const { return (&min)+2; }

    vec3<T>* data() { return &min; }

    T* raw_data() { return min.raw_data(); }
    static int raw_size() { return 2*vec3<T>::raw_size(); }
 };


using range3f = range3<float>;
using range3d = range3<double>;
using range3i = range3<int>;

template<typename T> inline bool isvalid(const range3<T>& a) { return min(a.min,a.max) == a.min; }

template<typename T> inline vec3<T> size(const range3<T>& a) { return (a.max-a.min); }
template<typename T> inline vec3<T> center(const range3<T>& a) { return (a.max+a.min)/2; }

template<typename T> inline range3<T> runion(const range3<T>& a, const vec3<T>& b) { if(not isvalid(a)) return range3<T>(b,b); return range3<T>(min(a.min,b),max(a.max,b)); }
template<typename T> inline range3<T> runion(const range3<T>& a, const range3<T>& b) { if(not isvalid(a)) return b; if(not isvalid(b)) return a; return range3<T>(min(a.min,b.min),max(a.max,b.max)); }

template<typename T> inline range3<T> rscale(const range3<T>& a, const T& b) { return range3<T>(center(a)-size(a)*b/2,center(a)+size(a)*b/2); }

template<typename T> inline array<vec3<T>,8> corners(const range3<T>& a) { array<vec3<T>,8> ret; ret[0] = vec3<T>(a.min.x,a.min.y,a.min.z); ret[1] = vec3<T>(a.min.x,a.min.y,a.max.z); ret[2] = vec3<T>(a.min.x,a.max.y,a.min.z); ret[3] = vec3<T>(a.min.x,a.max.y,a.max.z); ret[4] = vec3<T>(a.max.x,a.min.y,a.min.z); ret[5] = vec3<T>(a.max.x,a.min.y,a.max.z); ret[6] = vec3<T>(a.max.x,a.max.y,a.min.z); ret[7] = vec3<T>(a.max.x,a.max.y,a.max.z); return ret; }

template<typename T> inline range3<T> range_from_values(const vec3<T>& v0) { return range3<T>(v0,v0); }
template<typename T> inline range3<T> range_from_values(const vec3<T>& v0, const vec3<T>& v1) { return range3<T>(min(v0,v1),max(v0,v1)); }
template<typename T> inline range3<T> range_from_values(const vec3<T>& v0, const vec3<T>& v1, const vec3<T>& v2) { return range3<T>(min(v0,min(v1,v2)),max(v0,max(v1,v2))); }
template<typename T> inline range3<T> range_from_values(const vec3<T>& v0, const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3) { return range3<T>(min(v0,min(v1,min(v2,v3))),max(v0,max(v1,max(v2,v3)))); }

template<typename T> inline range3<T> range_from_values(const vec3<T>* v, int n) {
    auto ret = range3<T>();
    for(int i = 0; i < n; i ++) ret = runion(ret,v[i]);
    return ret;
}

#include <vector>
template<typename T> inline range3<T> range_from_values(const std::vector<vec3<T>>& v) {
    return range_from_values(v.data(),v.size());
}

#include <functional>
inline range3f range_from_func(const std::function<range3f(int)>& f, int n) {
    auto ret = range3f();
    for(int i = 0; i < n; i ++) ret = runion(ret,f(i));
    return ret;
}

inline range3f range_from_func(range3f (*f)(int), int n) {
    auto ret = range3f();
    for(int i = 0; i < n; i ++) ret = runion(ret,f(i));
    return ret;
}

template<typename T>
inline range3f range_from_func(T* ptr, range3f (*f)(T*,int), int n) {
    auto ret = range3f();
    for(int i = 0; i < n; i ++) ret = runion(ret,f(ptr,i));
    return ret;
}

#endif
