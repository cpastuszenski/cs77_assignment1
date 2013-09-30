#include "shape.h"

frame3f sphere_frame(Sphere* sphere, const vec2f& uv) {
    float phi = 2 * pi * uv.x;
    float theta = pi * uv.y;
    float ct = cos(theta);
    float st = sin(theta);
    float cp = cos(phi);
    float sp = sin(phi);
    frame3f frame;
    frame.o = sphere->r * vec3f(st*cp,st*sp,ct);
    frame.x = vec3f(sp,cp,0);
    frame.y = vec3f(ct*cp,ct*sp,st);
    frame.z = vec3f(st*cp,st*sp,ct);
    return frame;
}

frame3f cylinder_frame(Cylinder* cylinder, const vec2f& uv) {
    float phi = 2 * pif * uv.x;
    float hh = cylinder->h*uv.y;
    float cp = cos(phi);
    float sp = sin(phi);
    frame3f frame;
    frame.o = vec3f(cylinder->r*cp,cylinder->r*sp,hh);
    frame.x = vec3f(sp,cp,0);
    frame.y = z3f;
    frame.z = vec3f(cp,sp,0);
    return frame;
}

frame3f quad_frame(Quad* quad, const vec2f& uv) {
    auto f = identity_frame3f;
    f.o = f.x * (uv.x-0.5) * quad->w + f.y * (uv.y-0.5) * quad->h;
    return f;
}

frame3f triangle_frame(Triangle* triangle, const vec2f& uv) {
    frame3f f;
    f.x = normalize(triangle->v1-triangle->v0);
    f.y = normalize(triangle->v2-triangle->v0);
    f.z = normalize(cross(f.x,f.y));
    f.o = (triangle->v0+triangle->v1+triangle->v2)/3;
    f.o = triangle->v0*uv.x+triangle->v1*uv.y+triangle->v2*(1-uv.x-uv.y);
    return f;
}




