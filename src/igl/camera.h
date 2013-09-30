/*
 * File: camera.h
 *
 * Header file containing type definitions for the Camera days structure as
 * well as a function implemented for Assignment 1 that generates a ray from
 * a camera into a raytrace scene.
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "node.h"

struct Camera : Node {
    frame3f f = identity_frame3f;
    float   l = 1;
    float   w = 1;
    float   h = 1;
    float   d = 1;
};

inline int camera_image_width(Camera* camera, int r) {
    return (int)round(r * camera->w / camera->h);
}

inline int camera_image_height(Camera* camera, int r) {
    return r;
}

inline float camera_image_aspectratio(Camera* camera) {
    return camera->h/camera->w;
}

/* Given a camera and a point on the view plane, generates a
   ray from the camera into the scene we are raytracing */
inline ray3f camera_ray(Camera* camera, const vec2f& uv) {
    /* Construct a ray from camera to scene */
    vec3f o = zero3f;
    vec3f Q = vec3f((uv.x - 0.5) * camera->w, (uv.y - 0.5) * camera->h, -camera->d);
    vec3f d = vec3f(Q-o);
    /* Normalize it */
    d /= length(d);
    /* Transform it with respect to the camera's frame */
    return transform_ray(camera->f, ray3f(o, d));
}

#endif
