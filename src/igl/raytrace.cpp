/*
 * File: raytrace.cpp
 *
 * Contains a basic implementation of a raytracing algorithm that creates an image based upon
 * a scene of shapes and lights in 3D space and a set of raytracing options.
 */

#include "raytrace.h"

#include "vmath/random.h"
#include "intersect.h"

/* Function that calculates the color seen by a camera ray in a scene, given the scene, the ray,
   a set of raytrace options and a raytrace depth (used for reflections) */
vec3f _raytrace_scene_ray(Scene* scene, const ray3f& ray, const RaytraceOptions& opts, int depth) {
    /* Determine the nearest intersection in the scene */
    intersection3f intersection;
    if(not intersect_scene(scene,ray,intersection)) return opts.background;
    
    /* If the doublesided option is set, change surface orientation for shading */
    if(opts.doublesided) {
        intersection.f = faceforward(intersection.f,ray.d);
    }
    
    vec3f c = zero3f;
    
    /* Compute ambient lighting */
    vec3f ambient = material_diffuse_albedo(intersection.material) * opts.ambient;
    c += ambient;

    /* Compute direct lighting component */

    /* Calculate intersection point */
    vec3f p = ray.e + (intersection.t * ray.d);

    /* Calculate normal vector of intersection */
    vec3f normal = intersection.f.z;

    /* Calculate viewing direction of camera */
    vec3f w = -ray.d;

    /* For each light, shadow sample the point and determine the material BRDF of the light for
       the point */
    auto& ll = scene->lights;
    for(auto l : ll->lights) {
        ShadowSample ss = light_shadow_sample(l, p);

        vec3f light_intensity = ss.radiance;
        vec3f light_direction = ss.ray.d;

        /* Calculate visibility */
        int visibility = 1;
        if(intersect_scene(scene, ss.ray))
            visibility = 0;

        /* Our wi (incoming light) is light_direction, the wo (outgoing light) is the normalized
           negative direction vector of the camera ray */
        vec3f brdf = material_brdf(intersection.material, intersection.f, light_direction, w);

        c += light_intensity * (visibility * brdf * abs(dot(normal, light_direction)));
    }

    /* Recursively compute reflections, using the equations on page 81 of the lecture */
    if(opts.reflections and depth < opts.max_depth) {
        vec3f r = ray.d + 2 * dot(-ray.d, normal) * normal;
        ray3f intersection_ray = ray3f(p, r);
        // We must make sure the depth argument of the recursive call increases so we stop
        // eventually!
        vec3f reflection = material_reflection(intersection.material, intersection.f, w) *
                _raytrace_scene_ray(scene, intersection_ray, opts, depth + 1);

        c += reflection;
    }
    
    /* Return the calculated color of the pixel */
    return c;
}

/* Determine the color of pixels in a scene using the raytracing algorithm described on page 7 of
   the lecture. We perform the algorithm on a given scene and set of raytracing options. */
void raytrace_scene(image3f& img, Scene* scene, const RaytraceOptions& opts) {
    auto w = img.width();
    auto h = img.height();
    ray3f cam_ray;
    vec3f c = zero3f;

    /* Raytrace without supersampling (anti-aliasing), equivalent to pseudocode on page 93 */
    if(opts.samples == 1) {
        for(int i = 0; i < w; i++) {
            for(int j = 0; j < h; j++) {
                float u = (i + 0.5)/w;
                float v = (j + 0.5)/h;
                cam_ray = camera_ray(scene->camera, vec2f(u, v));
                c = _raytrace_scene_ray(scene, cam_ray, opts, 0);
                img.at(i, (h - 1) - j) = c;
            }
        }
    }
    /* Raytrace with supersampling (anti-aliasing), equivalent to pseudocode on page 94 */
    else {
        int s2 = max(1,(int)sqrt(opts.samples));

        /* This is the same code as above, we just subdivide each pixel into s2*s2 pixels
           and sample those and average their color to get the pixel's color */
        for(int i = 0; i < w; i++) {
            for(int j = 0; j < h; j++) {
                c = zero3f;
                for(int ii = 0; ii < s2; ii++) {
                    for(int jj = 0; jj < s2; jj++) {
                        float u = (i + (ii + 0.5)/s2)/w;
                        float v = (j + (jj + 0.5)/s2)/h;
                        cam_ray = camera_ray(scene->camera, vec2f(u, v));
                        c += _raytrace_scene_ray(scene, cam_ray, opts, 0);
                    }
                }
                img.at(i, (h - 1) - j) = c/opts.samples;
            }
        }
    }
}
