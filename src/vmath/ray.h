#ifndef _RAY_H_
#define _RAY_H_

#include "vec.h"

template<typename T>
struct ray3 {
    constexpr static const T epsilon = T(0.0001);
    constexpr static const T rayinf = T(1000000); // TODO: use numeric limits

    vec3<T> e = vec3<T>(0,0,0);
    vec3<T> d = vec3<T>(0,0,1);
    T tmin = epsilon;
    T tmax = rayinf;

    ray3() { }
    ray3(const vec3<T>& e, const vec3<T>& d, T tmin = epsilon, T tmax = rayinf) : 
        e(e), d(d), tmin(tmin), tmax(tmax) { }

    static ray3 segment(const vec3<T>& a, const vec3<T>& b) { return ray3<T>(a,normalize(b-a),epsilon,dist(a,b)-2*epsilon); }

    vec3<T> eval(T t) const { return e + d * t; }
};


using ray3f = ray3<float>;
using ray3d = ray3<double>;

#endif

