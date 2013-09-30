/*
 * File: material.h
 *
 * File that contains numerous functions for calculating material-based values for
 * use in raytracing, including BRDFs.
 */

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "node.h"

struct Material : Node {
};

struct Lambert : Material {
    vec3f        kd = vec3f(0.75,0.75,0.75);
};

struct Blinn : Material {
	vec3f        kd = vec3f(0.75,0.75,0.75);
    vec3f        ks = vec3f(0.25,0.25,0.25);
    float        n =  10;
    vec3f        kr = zero3f;
};

/* Calculate the BRDF for a material, given the local shading frame of the surface and vectors describing
   the direction from the point to the light and the point to the viewer/camera */
inline vec3f material_brdf(Material* material, const frame3f& f, const vec3f& wi, const vec3f& wo) {
    /* Calculate the Lambert BRDF using the equations on p. 57 */
    if(is<Lambert>(material)) {
        auto lambert = cast<Lambert>(material);
        if(dot(wi,f.z) <= 0 or dot(wo,f.z) <= 0) return zero3f; // Sanity check
        auto tkd = lambert->kd;
        return tkd;
    }
    /* Calculate the Blinn BRDF using the equations on p. 62 */
    else if(is<Blinn>(material)) {
        auto blinn = cast<Blinn>(material);
        if(dot(wi,f.z) <= 0 or dot(wo,f.z) <= 0) return zero3f; // Sanity check
        vec3f h = (wi + wo)/ length(wi+wo);
        auto tks = blinn->ks;
        auto tkd = blinn->kd;
        auto blinn_brdf = tkd + (tks * pow(max((float) 0.0, dot(f.z, h)), blinn->n));

        return blinn_brdf;
    }
    else { not_implemented_error(); return zero3f; }
}

/* Calculate the material diffuse albedo for a material */
inline vec3f material_diffuse_albedo(Material* material) {
    if(is<Lambert>(material)) {
        auto lambert = cast<Lambert>(material);
        return lambert->kd;
    } else if(is<Blinn>(material)) {
        auto blinn = cast<Blinn>(material);
        return blinn->kd;
    } else { not_implemented_error(); return zero3f; }
}

/* Calculate the material reflection for a material, given a shading frame and a light direction */
inline vec3f material_reflection(Material* material, const frame3f& f, const vec3f& w) {
    if(is<Lambert>(material)) return zero3f;
    else if(is<Blinn>(material)) {
        auto blinn = cast<Blinn>(material);        
        if(dot(w,f.z) <= 0) return zero3f; // Sanity check
        else return blinn->kr;
    }
    else { not_implemented_error(); return zero3f; }
}

#endif
