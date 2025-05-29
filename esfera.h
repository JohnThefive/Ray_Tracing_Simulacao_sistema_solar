#ifndef ESFERAH
#define ESFERAH

#include "hitable.h"
#include "vec3.h"
#include "ray.h"
#include "material.h" // Inclua o cabeçalho do material

class esfera : public hitable
{
public:
    esfera() : center(vec3(0, 0, 0)), radius(0), mat_ptr(nullptr) {}
    esfera(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    vec3 center;
    float radius;
    material *mat_ptr; // Ponteiro para o material
};

bool esfera::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        // Testa a menor raiz
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr; // Preenche o material no hit_record
            return true;
        }

        // Testa a maior raiz
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr; // Preenche o material no hit_record
            return true;
        }
    }
    return false;
}

vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.comprimento() >= 1.0);
    return p;
}

#endif