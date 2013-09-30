/*
 * File: geom.cpp
 *
 * File that contains a number of functions that determine whether a ray intersects a shape.
 * The shapes include triangles, spheres, cylinders, capped cylinders (EXTRA CREDIT) and quads.
 */

#include "geom.h"

/* Function that returns whether a ray intersects a triangle (defined by vectors v0, v1 and v2)
   and fills out values for the variables passed to the function corresponding to the distance
   from the intersection as well as the barycentric coordinates of the intersection */
bool intersect_triangle(const ray3f& ray,
                        const vec3f& v0, const vec3f& v1, const vec3f& v2,
                        float& t, float& ba, float& bb) {
    
    /* Using the equations on pages 38-41, determine whether the ray intersects
       the triangle */
    vec3f a = v0 - v2;
    vec3f b = v1 - v2;
    vec3f d = ray.d;
    vec3f e = ray.e - v2;

    float t1 = (dot(cross(e, a), b)) / (dot(cross(d, b), a));
    float alpha = (dot(cross(d, b), e)) / (dot(cross(d, b), a));
    float beta = (dot(cross(e, a), d)) / (dot(cross(d, b), a));

    bool t_valid = ((t1 <= ray.tmax) && (t1 >= ray.tmin));

    /* If we pass the test on page 40, we have an intersection, so fill out the
       t, ba, and bb values */
    if (t_valid && (alpha >= 0) && (beta >= 0) && ((alpha + beta) <= 1)) {
        t = t1;
        ba = alpha;   // barycentric coordinates of intersection
        bb = beta;
        return true;
    }
    else
        return false;
}

/* Function that returns whether a ray intersects a sphere and fills out a variable
   for the distance from the ray's origin to the intersection if there is one */
bool intersect_sphere(const ray3f& ray, const vec3f& o, float r, float& t) {
    
    /* Compute a, b, and c coefficients for polynomial */
    float a = dot(ray.d, ray.d);
    float b = dot((2 * ray.d),(ray.e - o));
    float c = dot((ray.e - o), (ray.e - o)) - (r * r);

    /* Find discriminant */
    float d = b * b - 4 * a * c;

    /* The ray misses the sphere if there are no real roots (the
       discriminant is negative) so we return false in this scenario */
    if (d < 0)
        return false;

    /* Determine whether we have an interesection using the equations on page
       of the lecture notes */
    auto tmin = (-b-sqrt(d)) / (2*a);
    auto tmax = (-b+sqrt(d)) / (2*a);

    /* Ensure t we choose is actually a valid value */
    bool tmin_within_range = ((tmin <= ray.tmax) && (tmin >= ray.tmin));
    bool tmax_within_range = ((tmax <= ray.tmax) && (tmax >= ray.tmin));

    if (tmin_within_range && tmax_within_range) {
        t = min(tmin, tmax);
        return true;
    }
    else if (tmin_within_range && !tmax_within_range) {
        t = tmin;
        return true;
    }
    else if (tmax_within_range && !tmin_within_range) {
        t = tmax;
        return true;
    }
    else
        return false;
}

// http://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
// http://www.gamedev.net/topic/467789-raycylinder-intersection/
bool intersect_cylinder(const ray3f& ray, float r, float h, float& t) {
    auto a = ray.d.x*ray.d.x+ray.d.y*ray.d.y;
    auto b = 2*ray.e.x*ray.d.x+2*ray.e.y*ray.d.y;
    auto c = ray.e.x*ray.e.x+ray.e.y*ray.e.y-r*r;
    auto d = b*b-4*a*c;
    if(d < 0) return false;
    auto tmin = (-b-sqrt(d)) / (2*a);
    auto tmax = (-b+sqrt(d)) / (2*a);
    auto zmin = ray.e.z+tmin*ray.d.z;
    auto zmax = ray.e.z+tmax*ray.d.z;
    if (tmin >= ray.tmin && tmin <= ray.tmax && zmin >= 0 && zmin <= h) {
        t = tmin;
        return true;
    }
    if (tmax >= ray.tmin && tmax <= ray.tmax && zmax >= 0 && zmax <= h) {
        t = tmax;
        return true;
    }
    return false;
}

/* EXTRA CREDIT */
/* Function that returns whether a ray intersects a capped cylinder and fills out a variable
   for the distance from the ray's origin to the intersection if there is one and also
   fills out the "type" of the intersection -- 1 for a cylinder body intersection, 2 for a top cap
   intersection, and 3 for a bottom cap intersection */
bool intersect_capped_cylinder(const ray3f& ray, float r, float h, float& t, int& type) {
    bool valid_intersect = false;
    t = ray.tmax;
    vec3f intersect = zero3f;
    /* Check whether the ray intersects the cylinder body,
       ensuring that the intersection is not between the end caps.
       Note: most of this code is from the previous function, written
       by Jon Denning */
    if(intersect_cylinder(ray, r, h, t)) {
            valid_intersect = true;
            type = BODY;
    }

    /* Now check the circles on top/bottom of cylinder
       http://orca.st.usm.edu/~jchen/courses/graphics/lectures/Raytracing.pdf
       proved helpful for this section of the code */

    /* Using the notes on ray-plane intersection... */
    /* Intersect the top end cap, first; intersect the plane at {0, 0, h} */
    vec3f n = vec3f(0, 0, 1); // Normal
    vec3f c = vec3f(0, 0, h); // Center
    float t_cap;
    if (dot(ray.d, n) != 0) {
        t_cap = dot((c-ray.e), n)/dot(ray.d, n);
        if (t_cap >= ray.tmin && t_cap <= ray.tmax) {
            intersect = ray.eval(t_cap);
            if((intersect.x * intersect.x + intersect.y * intersect.y) <= r*r) {
                if(t_cap < t) {
                    t = t_cap;
                    valid_intersect = true;
                    type = CAP_TOP;
                }
            }
        }
    }

    /* Intersect the bottom end cap; intersect the plane at {0, 0, 0} */
    n = vec3f(0, 0, -1);
    c = vec3f(0, 0, 0);
    if (dot(ray.d, n) != 0) {
        t_cap = dot((c-ray.e), n)/dot(ray.d, n);
        if (t_cap >= ray.tmin && t_cap <= ray.tmax) {
            intersect = ray.eval(t_cap);
            if((intersect.x * intersect.x + intersect.y * intersect.y) <= r*r) {
                if(t_cap < t) {
                    t = t_cap;
                    valid_intersect = true;
                    type = CAP_BOT;
                }
            }
        }
    }

    if(valid_intersect) return true;
    else return false;
}

bool intersect_quad(const ray3f& ray, float w, float h, float& t, float& ba, float& bb) {
    // TODO: BUG: handle infinite intersections
    if(ray.d.z == 0) return false;
    t = - ray.e.z / ray.d.z;
    if(t < ray.tmin or t > ray.tmax) return false;
    auto p = ray.eval(t);
    if(w/2 < p.x or -w/2 > p.x or h/2 < p.y or -h/2 > p.y) return false;
    ba = p.x/w+0.5;
    bb = p.y/h+0.5;
    return true;
}
