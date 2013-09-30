#ifndef _GEOM_H_
#define _GEOM_H_

#include "vec.h"
#include "ray.h"
#include "range.h"
#include "common/debug.h"

#define BODY 1
#define CAP_TOP 2
#define CAP_BOT 3

inline float atan2pos(float y, float x) { auto a = atan2(y,x); return (a >= 0) ? a : 2*pi+a; }

inline vec3f triangle_normal(const vec3f& v0, const vec3f& v1, const vec3f& v2) { return normalize(cross(v1-v0,v2-v0)); }

inline float sphere_volume(float r) { return 4*pi/3*r*r*r; }

inline vec3f quad_normal(const vec3f& v0, const vec3f& v1, const vec3f& v2, const vec3f& v3) { return normalize(triangle_normal(v0, v1, v2)+triangle_normal(v0, v2, v3)); }

bool intersect_triangle(const ray3f& ray, const vec3f& v0, const vec3f& v1, const vec3f& v2, float& t, float& ba, float& bb);
bool intersect_sphere(const ray3f& ray, const vec3f& o, float r, float& t);
bool intersect_quad(const ray3f& ray, float w, float h, float& t, float& ba, float& bb);
bool intersect_cylinder(const ray3f& ray, float r, float h, float& t);
bool intersect_capped_cylinder(const ray3f& ray, float r, float h, float& t, int& type);

inline bool intersect_triangle(const ray3f& ray, const vec3f& v0, const vec3f& v1, const vec3f& v2) { float t, ba, bb; return intersect_triangle(ray, v0, v1, v2, t, ba, bb); }
inline bool intersect_sphere(const ray3f& ray, const vec3f& o, float r) { float t; return intersect_sphere(ray, o, r, t); }
inline bool intersect_quad(const ray3f& ray, float w, float h) { float t, ba, bb; return intersect_quad(ray,w,h,t,ba,bb); }
inline bool intersect_cylinder(const ray3f& ray, float r, float h) { float t; return intersect_cylinder(ray,r,h,t); }

#endif
