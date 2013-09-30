#ifndef _VEC_H_
#define _VEC_H_

#include "stdmath.h"

template<typename T>
struct vec2 {
    typedef T base_type;

    T x, y;
    vec2() : x(0), y(0) { }
    vec2(const T& x, const T& y) : x(x), y(y) { }
    template<typename R> explicit vec2(const vec2<R>& v) : x(v.x), y(v.y) { }

    // template<typename S> operator vec2<S>() { return vec2<S>((S)x, (S)y); }

    T& operator[](int i) { return (&x)[i]; }
    const T& operator[](int i) const { return (&x)[i]; }

    static int size() { return 2; }

    T* begin() { return &x; }
    T* end() { return (&x)+2; }
    const T* begin() const { return &x; }
    const T* end() const { return (&x)+2; }

    T* data() { return &x; }
    const T* data() const { return &x; }

    T* raw_data() { return &x; }
    const T* raw_data() const { return &x; }
    static int raw_size() { return 2; }
};


using vec2f = vec2<float>;
const vec2f zero2f = vec2f(0, 0);
const vec2f one2f = vec2f(1, 1);
const vec2f x2f = vec2f(1, 0);
const vec2f y2f = vec2f(0, 1);

using vec2d = vec2<double>;
const vec2d zero2d = vec2d(0, 0);
const vec2d one2d = vec2d(1, 1);
const vec2d x2d = vec2d(1, 0);
const vec2d y2d = vec2d(0, 1);

using vec2i = vec2<int>;
const vec2i zero2i = vec2i(0, 0);
const vec2i one2i = vec2i(1, 1);

using vec2ub = vec2<unsigned char>;
const vec2ub zero2ub = vec2ub(0, 0);
const vec2ub one2ub = vec2ub(1, 1);

template<typename T> inline bool operator==(const vec2<T>& a, const vec2<T>& b) { return a.x==b.x and a.y==b.y; }
template<typename T> inline vec2<T> operator-(const vec2<T>& a) { return vec2<T>(-a.x, -a.y); }
template<typename T> inline vec2<T> operator+(const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x+b.x, a.y+b.y); }
template<typename T> inline vec2<T>& operator+=(vec2<T>& a, const vec2<T>& b) { a.x+=b.x; a.y+=b.y; return a; }
template<typename T> inline vec2<T> operator-(const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x-b.x, a.y-b.y); }
template<typename T> inline vec2<T>& operator-=(vec2<T>& a, const vec2<T>& b) { a.x-=b.x; a.y-=b.y; return a; }
template<typename T> inline vec2<T> operator*(const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x*b.x, a.y*b.y); }
template<typename T> inline vec2<T>& operator*=(vec2<T>& a, const vec2<T>& b) { a.x*=b.x; a.y*=b.y; return a; }
template<typename T> inline vec2<T> operator/(const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x/b.x, a.y/b.y); }
template<typename T> inline vec2<T>& operator/=(vec2<T>& a, const vec2<T>& b) { a.x/=b.x; a.y/=b.y; return a; }
template<typename T> inline vec2<T> operator*(const vec2<T>& a, const T& b) { return vec2<T>(a.x*b, a.y*b); }
template<typename T> inline vec2<T> operator*(const T& a, const vec2<T>& b) { return vec2<T>(a*b.x, a*b.y); }
template<typename T> inline vec2<T>& operator*=(vec2<T>& a, const T& b) { a.x*=b; a.y*=b; return a; }
template<typename T, typename R> inline vec2<T> operator*(const vec2<T>& a, const R& b) { return vec2<T>(a.x*b, a.y*b); }
template<typename T, typename R> inline vec2<T> operator*(const R& a, const vec2<T>& b) { return vec2<T>(a*b.x, a*b.y); }
template<typename T, typename R> inline vec2<T>& operator*=(vec2<T>& a, const R& b) { a.x*=b; a.y*=b; return a; }
template<typename T> inline vec2<T> operator/(const vec2<T>& a, const T& b) { return vec2<T>(a.x/b, a.y/b); }
template<typename T> inline vec2<T> operator/(const T& a, const vec2<T>& b) { return vec2<T>(a/b.x, a/b.y); }
template<typename T> inline vec2<T>& operator/=(vec2<T>& a, const T& b) { a.x/=b; a.y/=b; return a; }
template<typename T, typename R> inline vec2<T> operator/(const vec2<T>& a, const R& b) { return vec2<T>(a.x/b, a.y/b); }
template<typename T, typename R> inline vec2<T> operator/(const R& a, const vec2<T>& b) { return vec2<T>(a/b.x, a/b.y); }
template<typename T, typename R> inline vec2<T>& operator/=(vec2<T>& a, const R& b) { a.x/=b; a.y/=b; return a; }

template<typename T> inline vec2<T> max(const vec2<T>& a, const vec2<T>& b) { return vec2<T>(max(a.x,b.x), max(a.y,b.y)); }
template<typename T> inline vec2<T> max(const vec2<T>& a, const T& b) { return vec2<T>(max(a.x,b), max(a.y,b)); }
template<typename T> inline vec2<T> max(const T& a, const vec2<T>& b) { return vec2<T>(max(a,b.x), max(a,b.y)); }
template<typename T> inline vec2<T> min(const vec2<T>& a, const vec2<T>& b) { return vec2<T>(min(a.x,b.x), min(a.y,b.y)); }
template<typename T> inline vec2<T> min(const vec2<T>& a, const T& b) { return vec2<T>(min(a.x,b), min(a.y,b)); }
template<typename T> inline vec2<T> min(const T& a, const vec2<T>& b) { return vec2<T>(min(a,b.x), min(a,b.y)); }
template<typename T> inline vec2<T> clamp(const vec2<T>& x, const vec2<T>& m, const vec2<T>& M) { return vec2<T>(clamp(x.x,m.x,M.x), clamp(x.y,m.y,M.y)); }
template<typename T> inline vec2<T> clamp(const vec2<T>& x, const T& m, const T& M) { return vec2<T>(clamp(x.x,m,M), clamp(x.y,m,M)); }
template<typename T> inline T max_component(const vec2<T>& a) { T r = a.x; r = max(r,a.x); r = max(r,a.y);  return r; }
template<typename T> inline T min_component(const vec2<T>& a) { T r = a.x; r = min(r,a.x); r = min(r,a.y);  return r; }
template<typename T> inline T dot(const vec2<T>& a, const vec2<T>& b) { return a.x*b.x+a.y*b.y; }
template<typename T> inline T length(const vec2<T>& a) { return sqrt(dot(a,a)); }
template<typename T> inline T lengthSqr(const vec2<T>& a) { return dot(a,a); }
template<typename T> inline vec2<T> normalize(const vec2<T>& a) { auto l = length(a); if (l==0) return vec2<T>(0,0); else return a * 1/l; }
template<typename T> inline T dist(const vec2<T>& a, const vec2<T>& b) { return length(a-b); }
template<typename T> inline T distSqr(const vec2<T>& a, const vec2<T>& b) { return lengthSqr(a-b); }
template<typename T> inline void orthonormalize(vec2<T>& x, vec2<T>& y) { y = normalize(y); x = normalize(x - dot(x,y)*y); }

template<typename T>
struct vec3 {
    typedef T base_type;

    T x, y, z;
    vec3() : x(0), y(0), z(0) { }
    vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) { }
    template<typename R> explicit vec3(const vec3<R>& v) : x(v.x), y(v.y), z(v.z) { }

    // template<typename S> operator vec3<S>() { return vec3<S>((S)x, (S)y, (S)z); }

    T& operator[](int i) { return (&x)[i]; }
    const T& operator[](int i) const { return (&x)[i]; }

    static int size() { return 3; }

    T* begin() { return &x; }
    T* end() { return (&x)+3; }
    const T* begin() const { return &x; }
    const T* end() const { return (&x)+3; }

    T* data() { return &x; }
    const T* data() const { return &x; }

    T* raw_data() { return &x; }
    const T* raw_data() const { return &x; }
    static int raw_size() { return 3; }
};


using vec3f = vec3<float>;
const vec3f zero3f = vec3f(0, 0, 0);
const vec3f one3f = vec3f(1, 1, 1);
const vec3f x3f = vec3f(1, 0, 0);
const vec3f y3f = vec3f(0, 1, 0);
const vec3f z3f = vec3f(0, 0, 1);

using vec3d = vec3<double>;
const vec3d zero3d = vec3d(0, 0, 0);
const vec3d one3d = vec3d(1, 1, 1);
const vec3d x3d = vec3d(1, 0, 0);
const vec3d y3d = vec3d(0, 1, 0);
const vec3d z3d = vec3d(0, 0, 1);

using vec3i = vec3<int>;
const vec3i zero3i = vec3i(0, 0, 0);
const vec3i one3i = vec3i(1, 1, 1);

using vec3ub = vec3<unsigned char>;
const vec3ub zero3ub = vec3ub(0, 0, 0);
const vec3ub one3ub = vec3ub(1, 1, 1);

template<typename T> inline bool operator==(const vec3<T>& a, const vec3<T>& b) { return a.x==b.x and a.y==b.y and a.z==b.z; }
template<typename T> inline vec3<T> operator-(const vec3<T>& a) { return vec3<T>(-a.x, -a.y, -a.z); }
template<typename T> inline vec3<T> operator+(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(a.x+b.x, a.y+b.y, a.z+b.z); }
template<typename T> inline vec3<T>& operator+=(vec3<T>& a, const vec3<T>& b) { a.x+=b.x; a.y+=b.y; a.z+=b.z; return a; }
template<typename T> inline vec3<T> operator-(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(a.x-b.x, a.y-b.y, a.z-b.z); }
template<typename T> inline vec3<T>& operator-=(vec3<T>& a, const vec3<T>& b) { a.x-=b.x; a.y-=b.y; a.z-=b.z; return a; }
template<typename T> inline vec3<T> operator*(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(a.x*b.x, a.y*b.y, a.z*b.z); }
template<typename T> inline vec3<T>& operator*=(vec3<T>& a, const vec3<T>& b) { a.x*=b.x; a.y*=b.y; a.z*=b.z; return a; }
template<typename T> inline vec3<T> operator/(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(a.x/b.x, a.y/b.y, a.z/b.z); }
template<typename T> inline vec3<T>& operator/=(vec3<T>& a, const vec3<T>& b) { a.x/=b.x; a.y/=b.y; a.z/=b.z; return a; }
template<typename T> inline vec3<T> operator*(const vec3<T>& a, const T& b) { return vec3<T>(a.x*b, a.y*b, a.z*b); }
template<typename T> inline vec3<T> operator*(const T& a, const vec3<T>& b) { return vec3<T>(a*b.x, a*b.y, a*b.z); }
template<typename T> inline vec3<T>& operator*=(vec3<T>& a, const T& b) { a.x*=b; a.y*=b; a.z*=b; return a; }
template<typename T, typename R> inline vec3<T> operator*(const vec3<T>& a, const R& b) { return vec3<T>(a.x*b, a.y*b, a.z*b); }
template<typename T, typename R> inline vec3<T> operator*(const R& a, const vec3<T>& b) { return vec3<T>(a*b.x, a*b.y, a*b.z); }
template<typename T, typename R> inline vec3<T>& operator*=(vec3<T>& a, const R& b) { a.x*=b; a.y*=b; a.z*=b; return a; }
template<typename T> inline vec3<T> operator/(const vec3<T>& a, const T& b) { return vec3<T>(a.x/b, a.y/b, a.z/b); }
template<typename T> inline vec3<T> operator/(const T& a, const vec3<T>& b) { return vec3<T>(a/b.x, a/b.y, a/b.z); }
template<typename T> inline vec3<T>& operator/=(vec3<T>& a, const T& b) { a.x/=b; a.y/=b; a.z/=b; return a; }
template<typename T, typename R> inline vec3<T> operator/(const vec3<T>& a, const R& b) { return vec3<T>(a.x/b, a.y/b, a.z/b); }
template<typename T, typename R> inline vec3<T> operator/(const R& a, const vec3<T>& b) { return vec3<T>(a/b.x, a/b.y, a/b.z); }
template<typename T, typename R> inline vec3<T>& operator/=(vec3<T>& a, const R& b) { a.x/=b; a.y/=b; a.z/=b; return a; }

template<typename T> inline vec3<T> max(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(max(a.x,b.x), max(a.y,b.y), max(a.z,b.z)); }
template<typename T> inline vec3<T> max(const vec3<T>& a, const T& b) { return vec3<T>(max(a.x,b), max(a.y,b), max(a.z,b)); }
template<typename T> inline vec3<T> max(const T& a, const vec3<T>& b) { return vec3<T>(max(a,b.x), max(a,b.y), max(a,b.z)); }
template<typename T> inline vec3<T> min(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(min(a.x,b.x), min(a.y,b.y), min(a.z,b.z)); }
template<typename T> inline vec3<T> min(const vec3<T>& a, const T& b) { return vec3<T>(min(a.x,b), min(a.y,b), min(a.z,b)); }
template<typename T> inline vec3<T> min(const T& a, const vec3<T>& b) { return vec3<T>(min(a,b.x), min(a,b.y), min(a,b.z)); }
template<typename T> inline vec3<T> clamp(const vec3<T>& x, const vec3<T>& m, const vec3<T>& M) { return vec3<T>(clamp(x.x,m.x,M.x), clamp(x.y,m.y,M.y), clamp(x.z,m.z,M.z)); }
template<typename T> inline vec3<T> clamp(const vec3<T>& x, const T& m, const T& M) { return vec3<T>(clamp(x.x,m,M), clamp(x.y,m,M), clamp(x.z,m,M)); }
template<typename T> inline T max_component(const vec3<T>& a) { T r = a.x; r = max(r,a.x); r = max(r,a.y); r = max(r,a.z);  return r; }
template<typename T> inline T min_component(const vec3<T>& a) { T r = a.x; r = min(r,a.x); r = min(r,a.y); r = min(r,a.z);  return r; }
template<typename T> inline T dot(const vec3<T>& a, const vec3<T>& b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
template<typename T> inline T length(const vec3<T>& a) { return sqrt(dot(a,a)); }
template<typename T> inline T lengthSqr(const vec3<T>& a) { return dot(a,a); }
template<typename T> inline vec3<T> normalize(const vec3<T>& a) { auto l = length(a); if (l==0) return vec3<T>(0,0,0); else return a * 1/l; }
template<typename T> inline T dist(const vec3<T>& a, const vec3<T>& b) { return length(a-b); }
template<typename T> inline T distSqr(const vec3<T>& a, const vec3<T>& b) { return lengthSqr(a-b); }
template<typename T> inline vec3<T> cross(const vec3<T>& a, const vec3<T>& b) { return vec3<T>(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x); }      
template<typename T> inline void orthonormalize(vec3<T>& x, vec3<T>& y, vec3<T>& z) { z = normalize(z); x = normalize(cross(y,z)); y = normalize(cross(z,x)); }        
template<typename T> inline void orthonormalize(vec3<T>& x, vec3<T>& y) { y = normalize(y); x = normalize(x - dot(x,y)*y); }

// v is incoming
template<typename T> inline vec3<T> reflect(const vec3<T>& v, const vec3<T>& n) { return v - 2 * dot(n,v) * n; }        
template<typename T> inline vec3<T> faceforward(const vec3<T>& n, const vec3<T>& i, const vec3<T>& ng) { return dot(i, ng) < 0 ? n : -n; }        
template<typename T> inline vec3<T> faceforward(const vec3<T>& n, const vec3<T>& i) { return faceforward(n,i,n); }

template<typename T>
struct vec4 {
    typedef T base_type;

    T x, y, z, w;
    vec4() : x(0), y(0), z(0), w(0) { }
    vec4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) { }
    template<typename R> explicit vec4(const vec4<R>& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }

    // template<typename S> operator vec4<S>() { return vec4<S>((S)x, (S)y, (S)z, (S)w); }

    T& operator[](int i) { return (&x)[i]; }
    const T& operator[](int i) const { return (&x)[i]; }

    static int size() { return 4; }

    T* begin() { return &x; }
    T* end() { return (&x)+4; }
    const T* begin() const { return &x; }
    const T* end() const { return (&x)+4; }

    T* data() { return &x; }
    const T* data() const { return &x; }

    T* raw_data() { return &x; }
    const T* raw_data() const { return &x; }
    static int raw_size() { return 4; }
};


using vec4f = vec4<float>;
const vec4f zero4f = vec4f(0, 0, 0, 0);
const vec4f one4f = vec4f(1, 1, 1, 1);
const vec4f x4f = vec4f(1, 0, 0, 0);
const vec4f y4f = vec4f(0, 1, 0, 0);
const vec4f z4f = vec4f(0, 0, 1, 0);
const vec4f w4f = vec4f(0, 0, 0, 1);

using vec4d = vec4<double>;
const vec4d zero4d = vec4d(0, 0, 0, 0);
const vec4d one4d = vec4d(1, 1, 1, 1);
const vec4d x4d = vec4d(1, 0, 0, 0);
const vec4d y4d = vec4d(0, 1, 0, 0);
const vec4d z4d = vec4d(0, 0, 1, 0);
const vec4d w4d = vec4d(0, 0, 0, 1);

using vec4i = vec4<int>;
const vec4i zero4i = vec4i(0, 0, 0, 0);
const vec4i one4i = vec4i(1, 1, 1, 1);

using vec4ub = vec4<unsigned char>;
const vec4ub zero4ub = vec4ub(0, 0, 0, 0);
const vec4ub one4ub = vec4ub(1, 1, 1, 1);

template<typename T> inline bool operator==(const vec4<T>& a, const vec4<T>& b) { return a.x==b.x and a.y==b.y and a.z==b.z and a.w==b.w; }
template<typename T> inline vec4<T> operator-(const vec4<T>& a) { return vec4<T>(-a.x, -a.y, -a.z, -a.w); }
template<typename T> inline vec4<T> operator+(const vec4<T>& a, const vec4<T>& b) { return vec4<T>(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w); }
template<typename T> inline vec4<T>& operator+=(vec4<T>& a, const vec4<T>& b) { a.x+=b.x; a.y+=b.y; a.z+=b.z; a.w+=b.w; return a; }
template<typename T> inline vec4<T> operator-(const vec4<T>& a, const vec4<T>& b) { return vec4<T>(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w); }
template<typename T> inline vec4<T>& operator-=(vec4<T>& a, const vec4<T>& b) { a.x-=b.x; a.y-=b.y; a.z-=b.z; a.w-=b.w; return a; }
template<typename T> inline vec4<T> operator*(const vec4<T>& a, const vec4<T>& b) { return vec4<T>(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w); }
template<typename T> inline vec4<T>& operator*=(vec4<T>& a, const vec4<T>& b) { a.x*=b.x; a.y*=b.y; a.z*=b.z; a.w*=b.w; return a; }
template<typename T> inline vec4<T> operator/(const vec4<T>& a, const vec4<T>& b) { return vec4<T>(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w); }
template<typename T> inline vec4<T>& operator/=(vec4<T>& a, const vec4<T>& b) { a.x/=b.x; a.y/=b.y; a.z/=b.z; a.w/=b.w; return a; }
template<typename T> inline vec4<T> operator*(const vec4<T>& a, const T& b) { return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b); }
template<typename T> inline vec4<T> operator*(const T& a, const vec4<T>& b) { return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w); }
template<typename T> inline vec4<T>& operator*=(vec4<T>& a, const T& b) { a.x*=b; a.y*=b; a.z*=b; a.w*=b; return a; }
template<typename T, typename R> inline vec4<T> operator*(const vec4<T>& a, const R& b) { return vec4<T>(a.x*b, a.y*b, a.z*b, a.w*b); }
template<typename T, typename R> inline vec4<T> operator*(const R& a, const vec4<T>& b) { return vec4<T>(a*b.x, a*b.y, a*b.z, a*b.w); }
template<typename T, typename R> inline vec4<T>& operator*=(vec4<T>& a, const R& b) { a.x*=b; a.y*=b; a.z*=b; a.w*=b; return a; }
template<typename T> inline vec4<T> operator/(const vec4<T>& a, const T& b) { return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b); }
template<typename T> inline vec4<T> operator/(const T& a, const vec4<T>& b) { return vec4<T>(a/b.x, a/b.y, a/b.z, a/b.w); }
template<typename T> inline vec4<T>& operator/=(vec4<T>& a, const T& b) { a.x/=b; a.y/=b; a.z/=b; a.w/=b; return a; }
template<typename T, typename R> inline vec4<T> operator/(const vec4<T>& a, const R& b) { return vec4<T>(a.x/b, a.y/b, a.z/b, a.w/b); }
template<typename T, typename R> inline vec4<T> operator/(const R& a, const vec4<T>& b) { return vec4<T>(a/b.x, a/b.y, a/b.z, a/b.w); }
template<typename T, typename R> inline vec4<T>& operator/=(vec4<T>& a, const R& b) { a.x/=b; a.y/=b; a.z/=b; a.w/=b; return a; }

template<typename T> inline vec4<T> max(const vec4<T>& a, const vec4<T>& b) { return vec4<T>(max(a.x,b.x), max(a.y,b.y), max(a.z,b.z), max(a.w,b.w)); }
template<typename T> inline vec4<T> max(const vec4<T>& a, const T& b) { return vec4<T>(max(a.x,b), max(a.y,b), max(a.z,b), max(a.w,b)); }
template<typename T> inline vec4<T> max(const T& a, const vec4<T>& b) { return vec4<T>(max(a,b.x), max(a,b.y), max(a,b.z), max(a,b.w)); }
template<typename T> inline vec4<T> min(const vec4<T>& a, const vec4<T>& b) { return vec4<T>(min(a.x,b.x), min(a.y,b.y), min(a.z,b.z), min(a.w,b.w)); }
template<typename T> inline vec4<T> min(const vec4<T>& a, const T& b) { return vec4<T>(min(a.x,b), min(a.y,b), min(a.z,b), min(a.w,b)); }
template<typename T> inline vec4<T> min(const T& a, const vec4<T>& b) { return vec4<T>(min(a,b.x), min(a,b.y), min(a,b.z), min(a,b.w)); }
template<typename T> inline vec4<T> clamp(const vec4<T>& x, const vec4<T>& m, const vec4<T>& M) { return vec4<T>(clamp(x.x,m.x,M.x), clamp(x.y,m.y,M.y), clamp(x.z,m.z,M.z), clamp(x.w,m.w,M.w)); }
template<typename T> inline vec4<T> clamp(const vec4<T>& x, const T& m, const T& M) { return vec4<T>(clamp(x.x,m,M), clamp(x.y,m,M), clamp(x.z,m,M), clamp(x.w,m,M)); }
template<typename T> inline T max_component(const vec4<T>& a) { T r = a.x; r = max(r,a.x); r = max(r,a.y); r = max(r,a.z); r = max(r,a.w);  return r; }
template<typename T> inline T min_component(const vec4<T>& a) { T r = a.x; r = min(r,a.x); r = min(r,a.y); r = min(r,a.z); r = min(r,a.w);  return r; }
template<typename T> inline T dot(const vec4<T>& a, const vec4<T>& b) { return a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w; }
template<typename T> inline T length(const vec4<T>& a) { return sqrt(dot(a,a)); }
template<typename T> inline T lengthSqr(const vec4<T>& a) { return dot(a,a); }
template<typename T> inline vec4<T> normalize(const vec4<T>& a) { auto l = length(a); if (l==0) return vec4<T>(0,0,0,0); else return a * 1/l; }
template<typename T> inline T dist(const vec4<T>& a, const vec4<T>& b) { return length(a-b); }
template<typename T> inline T distSqr(const vec4<T>& a, const vec4<T>& b) { return lengthSqr(a-b); }

template<typename T> inline vec3<T> rotate_elements(vec3<T> v, int c) {
    c = ((c%3)+3)%3;
    if( c == 0 ) return v;
    if( c == 1 ) return vec3<T>( v.y, v.z, v.x );
    return vec3<T>( v.z, v.x, v.y );
}
template<typename T> inline vec4<T> rotate_elements(vec4<T> v, int c) {
    c = ((c%4)+4)%4;
    if( c == 0 ) return v;
    if( c == 1 ) return vec4<T>( v.y, v.z, v.w, v.x );
    if( c == 2 ) return vec4<T>( v.z, v.w, v.x, v.y );
    return vec4<T>( v.w, v.x, v.y, v.z );
}



#endif

