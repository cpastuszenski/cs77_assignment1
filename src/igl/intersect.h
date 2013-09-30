#ifndef _INTERSECT_H_
#define _INTERSECT_H_

#include "vmath/vmath.h"
#include "common/std.h"

#define BODY 1
#define CAP_TOP 2
#define CAP_BOT 3

struct Material;
struct Scene;
struct Shape;

struct intersection3f {
	float     t;
	frame3f   f;
	Material* material;
};

inline intersection3f transform_intersection(const frame3f& frame, const intersection3f& intersection) {
    auto ret = intersection;
    ret.f = transform_frame(frame,intersection.f);
    return ret;
}

inline intersection3f transform_intersection(const mat4f& m, const mat4f& mi, const intersection3f& intersection) {
    auto ret = intersection;
    ret.f = transform_frame(m,intersection.f);
    return ret;
}

bool intersect_scene(Scene* scene, const ray3f& ray, intersection3f& intersection);
bool intersect_scene(Scene* scene, const ray3f& ray);

#endif
