#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit result;
    vec3 distToCenter = ray.endpoint - center;
    double b = dot(ray.direction*2, distToCenter);
    double C = dot(distToCenter, distToCenter) - (radius*radius);
    double discriminant = b*b - (4*C);

    if (discriminant <= 0) { //no intersection
        result.object = 0; //SEGFAULT fixing... IT WORKED!!! Turns out Sphere intersection was returning a bad pointer because it was never set to anything...
        return result;
    }
    else {
        double t1;
        double t2;


        t2 = (-b - sqrt(discriminant))/2;
        t1 = (-b + sqrt(discriminant))/2;

        if ((t2 > 0) and (t2 >= small_t)) {
            result.dist = t2;
            result.object = this;
        }
        else if ((t1 > 0) and (t2 >= t1) and (t1 >= small_t)) {
            result.dist = t1;
            result.object = this;
        }
    }
    //dot product of (ray.Point(closestHit.dist) - sphere_center) - radius^2 = 0
    //ends up becoming t^2 + bt + C = 0 where C == (rayPoint-sphereCenter)dot(rayPoint-sphereCenter)-r^2
    //if b^2-4C <= 0, no intersection
    //if b^2-4C > 0, find t1 and t2 and return the smallest t that solves the equation
    //t1,2 == (-b +/- sqrt(b^2-4C))/2
    //compute t2 = -b/2 - d, check t2 > 0, if it is you're done
    //else if t2 < 0, check if t1 > 0 and then return that result


    return result;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = point - center;
    return normal.normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
