/*
 * File: light.h
 *
 * File that contains light-related data structures and a function that computes
 * a shadow sample, useful in raytracing.
 *
 */

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "node.h"
#include "shape.h"

struct ShadowSample {
    vec3f           radiance;
    ray3f           ray;
};

struct Light : Node {
    frame3f             f = identity_frame3f;
};

struct PointLight : Light {
    vec3f               intensity = one3f;
};

struct DirectionalLight : Light {
    vec3f               intensity = one3f;
};

struct LightGroup : Node {
    vector<Light*>      lights;
};

/* Function that computes a shadow sample given a light and a surface point */
inline ShadowSample light_shadow_sample(Light* light, const vec3f& p) {
    /* Transform the surface point back to world coordinates */
    auto pl = transform_point_inverse(light->f, p);
    ShadowSample ss;
    /* If the light is a point light, use the equations on p. 68 of the
       notes to calculate the shadow sample's ray and radiance */
    if(is<PointLight>(light)) {
        auto pointlight = cast<PointLight>(light);
        ss.ray = ray3f::segment(pl, zero3f);
        ss.radiance = pointlight->intensity / pow(length(pl), 2);
    }
    /* Else, do the same thing for a directional light using the
       equations on p. 69 */
    else if(is<DirectionalLight>(light)) {
        auto directionallight = cast<DirectionalLight>(light);
        ss.ray = ray3f(pl,-z3f);
        ss.radiance = directionallight->intensity;
    }
    else { not_implemented_error(); }
    /* Transform the shadow sample ray back to coordinates relative to the frame */
    ss.ray = transform_ray(light->f, ss.ray);
    return ss;
}

#endif
