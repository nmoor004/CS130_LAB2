#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; // determine the color
    vec3 r = 2*dot(normal, -ray.direction)*normal + (ray.direction);
    Ray reflected_ray(intersection_point, r);

    if (recursion_depth >= world.recursion_depth_limit) {
        color = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
        return color;
    }
    else {
        color = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth) + reflectivity*world.Cast_Ray(reflected_ray, recursion_depth+1);
    }


    return color;

    //color = ...
    //compute reflected ray
    // reflected_ray = u - 2*n*n_Tu
    //k is reflectivity, k = 0 is not reflective, k = 1 is purely reflective
    //color = (1-k) * color + k * cast_ray(reflected ray)
}
