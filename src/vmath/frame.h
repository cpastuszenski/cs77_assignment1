#ifndef _FRAME_H_
#define _FRAME_H_

#include "vec.h"

template<typename T>
struct frame2 {
    vec2<T> o, x, y;

    explicit frame2() : o(0, 0), x(1, 0), y(0, 1) { }
    explicit frame2(const vec2<T>& o, const vec2<T>& x, const vec2<T>& y) : o(o), x(x), y(y) { }
};


using frame2f = frame2<float>;
using frame2d = frame2<double>;

const frame2f identity_frame2f = frame2f();
const frame2d identity_frame2d = frame2d();

template<typename T>
struct frame3 {
    vec3<T> o, x, y, z;

    explicit frame3() : o(0, 0, 0), x(1, 0, 0), y(0, 1, 0), z(0, 0, 1) { }
    explicit frame3(const vec3<T>& o, const vec3<T>& x, const vec3<T>& y, const vec3<T>& z) : o(o), x(x), y(y), z(z) { }
};


using frame3f = frame3<float>;
using frame3d = frame3<double>;

const frame3f identity_frame3f = frame3f();
const frame3d identity_frame3d = frame3d();

template<typename T> inline frame3<T> inverse(const frame3<T>& f) { return frame3<T>(vec3<T>(-dot(f.o,f.x), -dot(f.o,f.y), -dot(f.o,f.z)), vec3<T>(f.x.x, f.y.x, f.z.x),vec3<T>(f.x.y, f.y.y, f.z.y),vec3<T>(f.x.z, f.y.z, f.z.z)); }
template<typename T> inline frame3<T> orthonormalize(const frame3<T>& f) { frame3<T> ret = f; orthonormalize(ret.x, ret.y, ret.z); return ret; }
template<typename T> inline frame3<T> faceforward(const frame3<T>& f, const vec3<T>& d, const vec3<T>& ng) { frame3<T> ret = f; ret.z = faceforward(ret.z,d,ng); ret.y = faceforward(ret.y,d,ng); return ret; }
template<typename T> inline frame3<T> faceforward(const frame3<T>& f, const vec3<T>& d) { return faceforward(f,d,f.z); }

template<typename T> inline frame3<T> lookat_frame(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up, bool flipped = false) { auto f = frame3<T>(); f.o = eye; f.z = normalize(center-eye); if(flipped) f.z = -f.z; f.y = up; f = orthonormalize(f); return f;
}

#endif
