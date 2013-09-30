/*
 * File: intersect.c
 *
 * File containing functions that determine whether rays interesect with primitives/shapes
 * in a scene we are raytracing.
 *
 */

#include "intersect.h"

#include "scene.h"

/* Function that determines whether a ray intersects a shape in a scene, given
   the shape in question, a ray, and an intersection data structure */
bool intersect_shape(Shape* shape, const ray3f& ray, intersection3f& intersection) {
    if(is<Sphere>(shape)) {
        auto sphere = cast<Sphere>(shape);
        
        /* Determine whether the ray intersects the sphere, with our function */
        float t;
        vec3f o = zero3f;
        if(not intersect_sphere(ray, o, sphere->r, t)) return false;
        
        /* If it intersects, calculate pl and the x and y of the sphere's frame
           with the equations given in lecture */
        auto pl = (ray.eval(t) - o)/sphere->r;
        auto uv = vec2f(atan2pos(pl.y, pl.x)/ (2*PIf), acos(pl.z) / PIf);

        /* Set the distance from the intersection
           and build a shading frame for the intersection with the given frame function */
        intersection.t = t;
        intersection.f = sphere_frame(sphere, uv);
        return true;

    }
    else if(is<Cylinder>(shape)) {
        auto cylinder = cast<Cylinder>(shape);
        
        float t;
        if(not intersect_cylinder(ray, cylinder->r, cylinder->h, t)) return false;
        
        auto pl = ray.eval(t) / vec3f(cylinder->r,cylinder->r,cylinder->h);
        auto uv = vec2f(atan2pos(pl.y,pl.x)/(2*pi),pl.z);
        
        intersection.t = t;
        intersection.f = cylinder_frame(cylinder, uv);
        
        return true;
    }
    else if(is<CappedCylinder>(shape)) {
        auto cylinder = cast<CappedCylinder>(shape);

        float t;
        int type;
        if(not intersect_capped_cylinder(ray, cylinder->r, cylinder->h, t, type)) return false;

        // If we hit the cylinder body
        if(type == BODY) {
            auto pl = ray.eval(t) / vec3f(cylinder->r,cylinder->r,cylinder->h);
            auto uv = vec2f(atan2pos(pl.y,pl.x)/(2*pi),pl.z);
            intersection.f = cylinder_frame((Cylinder *) cylinder, uv);
        }
        // If we hit the caps
        else {
            intersection.f.x = vec3f(1,0,0);
            intersection.f.y = vec3f(0,1,0);
            if(type == CAP_TOP)
                intersection.f.z = vec3f(0,0,1);
            else
                intersection.f.z = vec3f(0,0,-1);
        }
        intersection.t = t;
        return true;
    }
    else if(is<Quad>(shape)) {
        auto quad = cast<Quad>(shape);
        
        float t; vec2f uv;
        if(not intersect_quad(ray, quad->w, quad->h, t, uv.x, uv.y)) return false;
        
        intersection.t = t;
        intersection.f = quad_frame(quad,uv);
        
        return true;
    }
    else if(is<Triangle>(shape)) {
        auto triangle = cast<Triangle>(shape);
        
        /* Determine whether the ray intersects the triangle, with our function */
        float t;
        vec2f uv;
        if(not intersect_triangle(ray, triangle->v0, triangle->v1, triangle->v2, t, uv.x, uv.y)) return false;

        /* Set the distance from the intersection
           and build a shading frame for the intersection with the given frame function */
        intersection.t = t;
        intersection.f = triangle_frame(triangle, uv);
        
        return true;
    }
    else { not_implemented_error(); return false; }
}

/* Determines whether a primitive is intersected by a ray, and if it is, fills the
   given intersection data structure with relevant information */
bool intersect_primitive(Primitive* prim, const ray3f& ray, intersection3f& intersection) {
    /* If the surface is a primitive, check if the primitive is intersected by the ray.
       If it is, set the material of the intersection and transform the intersection frame
       relative to the frame of the primitive */
    if(is<Surface>(prim)) {
        auto surf = cast<Surface>(prim);
        if (intersect_shape(surf->shape, transform_ray_inverse(prim->f, ray), intersection)) {
            intersection.material = prim->material;
            intersection.f = transform_frame(prim->f, intersection.f);
            return true;
        }
        /* Else return false */
        return false;
    } else { not_implemented_error(); return false; }
}

/* Determines whether a group of primitives is intersected by a ray, and if it is, fills the
   given intersection data structure with relevant information */
bool intersect_primitives(PrimitiveGroup* group, const ray3f& ray, intersection3f& intersection) {

    intersection3f temp;
    temp.t = ray.tmax;
    bool intersect = false;

    /* Loop through all primitives in the group, checking whether they are intersected by the ray
       Ensure the closest intersection is stored in "intersection" */
    for(auto it : group->prims) {
        if(intersect_primitive(it, ray, intersection)) {
            if(intersection.t < temp.t){
                intersect = true;
                temp = intersection;
            }
        }

    }
    
    /* Set intersection and return whether there was an intersection or not */
    intersection = temp;
    return intersect;
}

/* Different declarations of the same function that returns whether a ray intersects
   any of the primitives in a scene. Further, the function will populate intersection
   with information about the closest intersection in the scene to the ray if there
   is an intersection */
bool intersect_scene(Scene* scene, const ray3f& ray, intersection3f& intersection) {
    return intersect_primitives(scene->prims, ray, intersection);
}

bool intersect_scene(Scene* scene, const ray3f& ray) {
    intersection3f intersection;
    return intersect_primitives(scene->prims, ray, intersection);
}

