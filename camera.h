#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "vec3.h"

class camera
{
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect_ratio)
    {
        float theta = vfov * M_PI / 180.0; // Converte o FOV para radianos
        float h = tan(theta / 2);          // Calcula a altura do viewport
        float viewport_height = 2.0 * h;
        float viewport_width = aspect_ratio * viewport_height;

        // Calcula os vetores da câmera
        vec3 w = unit_vector(lookfrom - lookat);       // Vetor direção para trás
        vec3 u = unit_vector(produtoVetorial(vup, w)); // Vetor horizontal
        vec3 v = produtoVetorial(w, u);                // Vetor vertical

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - w;
    }

    ray pegar_raio(float u, float v) const
    {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif
