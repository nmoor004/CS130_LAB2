#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{

    Hit closestIntersect;
    closestIntersect.object = 0;
    closestIntersect.dist = std::numeric_limits<double>::max();
    closestIntersect.part = -1;

    Hit checkIntersect;

    //TODO;

   /* if (this->objects.size() > 0) {
        closestIntersect = objects[0]->Intersection(ray, -1);
       // SEGFAULT; DONT DO THIS
       // changed unsigned int i to 0, 12 points now that i fixed this
        */

        for (unsigned int i = 0; i < objects.size(); i++) {
            checkIntersect = objects[i]->Intersection(ray, -1);
            if (checkIntersect.dist < closestIntersect.dist and checkIntersect.dist >= small_t) {
                closestIntersect = checkIntersect;
            }
        }


    return closestIntersect;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray;
    ray.direction = (camera.World_Position(pixel_index) - camera.position).normalized(); //todo
    ray.endpoint = camera.position; //todo

    vec3 color=Cast_Ray(ray, 1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));


}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();
    //set min_t to a large value?? where?
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    //TODO; // determine the color here
    Hit closestHit = Closest_Intersection(ray);
    if (closestHit.object != 0) {

        color = closestHit.object->material_shader->Shade_Surface(
                ray,
                ray.Point(closestHit.dist),
                closestHit.object->Normal(ray.Point(closestHit.dist),closestHit.part),
                recursion_depth);
    } //SEGFAULT????
    else if (closestHit.object == 0) { //Nothing was hit by this ray
        color = background_shader->Shade_Surface(ray, ray.endpoint, ray.endpoint, recursion_depth); // just gonna use ray.endpoint as a throw away lolol
    }

    return color;
}

void Render_World::Initialize_Hierarchy()
{
    //TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
