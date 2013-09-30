#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "node.h"

struct Shape : Node { };

struct Sphere : Shape {
    float           r = 1;
};

struct Cylinder : Shape {
    float           r = 1;
    float           h = 1;
};

struct CappedCylinder : Shape {
    float           r = 1;
    float           h = 1;
};

struct Quad : Shape {
    float           w = 1;
    float           h = 1;
};

struct Triangle : Shape {
    vec3f           v0 = vec3f(cos(radians( 90.0f)),sin(radians( 90.0f)),0.0f);
    vec3f           v1 = vec3f(cos(radians(210.0f)),sin(radians(210.0f)),0.0f);
    vec3f           v2 = vec3f(cos(radians(330.0f)),sin(radians(330.0f)),0.0f);
};


frame3f sphere_frame(Sphere* sphere, const vec2f& uv);
frame3f cylinder_frame(Cylinder* cylinder, const vec2f& uv);
frame3f quad_frame(Quad* quad, const vec2f& uv);
frame3f triangle_frame(Triangle* triangle, const vec2f& uv);

#endif
