#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 COLOR_a;
    vec3 COLOR_d;
    vec3 COLOR_s;
    //TODO; //determine the color

    //Since each light stores Render_World by reference, iterate thru all lights and get their emitted light
    //COLOR = COLOR_a + COLOR_d + COLOR_s
    //COLOR_a = RGB_Material_a * LIGHT_INTENSITY
    //COLOR_d = RGB_Material_d * LIGHT_INTENSITY * max(ndot1, 0)
    //COLOR_s = RGB_Material_s * LIGHT_INTENSITY * max(cos phi, 0)^alpha

    //Determine ambient
    COLOR_a = color_ambient * world.ambient_color * world.ambient_intensity;

    //Determine diffuse
    for (unsigned int i = 0; i < world.lights.size(); i++) {
        Light* currentLight = world.lights[i];
        Ray vector_to_light;
        vector_to_light.endpoint = intersection_point;
        vector_to_light.direction  = (currentLight->position - intersection_point).normalized();

        COLOR_d = COLOR_d + color_diffuse*currentLight->Emitted_Light(currentLight->position - intersection_point)*std::max(dot(normal, vector_to_light.direction), static_cast<double>(0));

        //Determine specular
        vec3 v = -(ray.direction);
        vec3 reflected = (-(currentLight->position - intersection_point) + 2 * dot(normal, (currentLight->position - intersection_point))*normal).normalized(); //lecture 7 r=l + 2(nDOTl)*n

        COLOR_s = COLOR_s + color_specular*currentLight->Emitted_Light(currentLight->position - intersection_point)*std::pow(std::max(dot(v, reflected), static_cast<double>(0)), specular_power);

    }



    //Sum
    color = COLOR_a + COLOR_d + COLOR_s;
    return color;
}
