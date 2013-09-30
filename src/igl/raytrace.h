#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

#include "scene.h"
#include "image.h"

struct RaytraceOptions : Node {
    int   res         = 512;
    int   samples     = 4;
    bool  doublesided = true;
    float time        = 0;
    float shutter     = 1;
    
    vec3f background  = {0.25,0.25,0.25};
    vec3f ambient     = {0.2,0.2,0.2};
    
    bool  shadows     = true;
    bool  reflections = true;
    int   max_depth   = 4;
};

void raytrace_scene(image3f& img, Scene* scene, const RaytraceOptions& opts);

#endif