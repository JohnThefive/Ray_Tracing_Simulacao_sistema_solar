#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray
{
public:
    // Construtor padrão: inicializa o raio com origem e direção nulas.
    ray() : A(vec3(0, 0, 0)), B(vec3(0, 0, 0)) {}

    // Construtor parametrizado: inicializa o raio com uma origem 'a' e uma direção 'b'.
    ray(const vec3 &a, const vec3 &b) : A(a), B(b) {}

    // Função que retorna a origem do raio.
    vec3 origin() const { return A; }

    // Função que retorna a direção do raio.
    vec3 direction() const { return B; }

    // Função que calcula um ponto no raio dado um parâmetro 't'.
    // 't' é a distância ao longo da direção do raio.
    vec3 point_at_parameter(float t) const { return A + t * B; }

private:
    vec3 A, B; // 'A' é a origem do raio e 'B' é a direção do raio.
};

#endif
