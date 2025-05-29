#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hitable.h"
#include "vec3.h"
#include "esfera.h"

class material
{
public:
    virtual bool espalhamento(const ray &r_in, const hit_record &rec, vec3 &atenuacao, ray &espalhamento) const = 0;

    // Método para emissão, padrão é preto (sem emissão)
    virtual vec3 emitir() const
    {
        return vec3(0, 0, 0);
    }
};

vec3 random_in_unit_sphere();
class lambertian : public material
{
public:
    vec3 albedo;

    lambertian(const vec3 &a) : albedo(a) {}

    virtual bool espalhamento(const ray &r_in, const hit_record &rec, vec3 &atenuacao, ray &espalhamento) const override
    {
        vec3 alvo = rec.p + rec.normal + random_in_unit_sphere();
        espalhamento = ray(rec.p, alvo - rec.p);
        atenuacao = albedo;
        return true;
    }
};

class emissive : public material
{
public:
    emissive(const vec3 &cor_emissao) : emit(cor_emissao) {}

    // Emissão retorna a cor do material emissivo
    virtual vec3 emitir() const override // Corrigido para não ter parâmetros
    {
        return emit; // Emissão pode ser constante ou dependente de p
    }

    // Materiais emissivos não espalham luz, apenas emitem
    virtual bool espalhamento(const ray &r_in, const hit_record &rec, vec3 &atenuacao, ray &espalhamento) const override
    {
        return false; // Sem espalhamento
    }

private:
    vec3 emit; // Cor da emissão
};

#endif