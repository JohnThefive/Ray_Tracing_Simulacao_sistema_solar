#ifndef HITABLE_LISTAH
#define HITABLE_LISTAH

#include "hitable.h"

class hitable_lista : public hitable
{
public:
    hitable_lista() : lista(nullptr), tamanho_da_lista(0) {}
    hitable_lista(hitable **l, int n) : lista(l), tamanho_da_lista(n) {}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    hitable **lista;
    int tamanho_da_lista;
};

bool hitable_lista::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (int i = 0; i < tamanho_da_lista; i++)
    {
        if (lista[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif
