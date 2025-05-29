#ifndef VEC3H
#define VEC3H

#include <iostream>
#include <cmath>
#include <cstdlib>

class vec3
{
public:
    // Construtores
    vec3() : componentes{0, 0, 0} {}                          // Construtor padrão
    vec3(float x, float y, float z) : componentes{x, y, z} {} // Construtor com parâmetros

    // Getters
    inline float obter_x() const { return componentes[0]; }
    inline float obter_y() const { return componentes[1]; }
    inline float obter_z() const { return componentes[2]; }

    // Operadores unários
    inline const vec3 &operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-componentes[0], -componentes[1], -componentes[2]); }

    // Operadores de acesso
    inline float operator[](int i) const { return componentes[i]; }
    inline float &operator[](int i) { return componentes[i]; }

    // Operadores aritméticos
    inline vec3 operator+(const vec3 &v) const;
    inline vec3 operator-(const vec3 &v) const;
    inline vec3 operator*(const vec3 &v) const; // Produto ponto
    inline vec3 operator/(const vec3 &v) const; // Divisão por componente
    inline vec3 operator*(float escalar) const;
    inline vec3 operator/(float escalar) const;

    inline vec3 &operator+=(const vec3 &v);
    inline vec3 &operator-=(const vec3 &v);
    inline vec3 &operator*=(const vec3 &v);
    inline vec3 &operator/=(const vec3 &v);
    inline vec3 &operator*=(float escalar);
    inline vec3 &operator/=(float escalar);

    // Normalização do vetor
    inline void normalizar();

    // Comprimento do vetor
    inline float comprimento() const
    {
        return sqrt(componentes[0] * componentes[0] +
                    componentes[1] * componentes[1] +
                    componentes[2] * componentes[2]);
    }

    float componentes[3]; // Componentes do vetor
};

// Operadores externos
inline std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    os << v.componentes[0] << " " << v.componentes[1] << " " << v.componentes[2];
    return os;
}

// Implementação dos operadores aritméticos binários
inline vec3 vec3::operator+(const vec3 &v) const
{
    return vec3(componentes[0] + v.componentes[0], componentes[1] + v.componentes[1], componentes[2] + v.componentes[2]);
}

// Operador de multiplicação de um escalar por um vetor (float * vec3)
inline vec3 operator*(float escalar, const vec3 &v)
{
    return vec3(v.obter_x() * escalar, v.obter_y() * escalar, v.obter_z() * escalar);
}

inline float dot(const vec3 &v1, const vec3 &v2)
{
    return v1.obter_x() * v2.obter_x() +
           v1.obter_y() * v2.obter_y() +
           v1.obter_z() * v2.obter_z();
}

// Produto vetorial entre dois vetores
inline vec3 produtoVetorial(const vec3 &v1, const vec3 &v2)
{
    return vec3(
        v1.obter_y() * v2.obter_z() - v1.obter_z() * v2.obter_y(),
        v1.obter_z() * v2.obter_x() - v1.obter_x() * v2.obter_z(),
        v1.obter_x() * v2.obter_y() - v1.obter_y() * v2.obter_x());
}

// Função para retornar o vetor unitário
inline vec3 unit_vector(const vec3 &v)
{
    vec3 copy = v;
    copy.normalizar();
    return copy;
}

inline vec3 vec3::operator-(const vec3 &v) const
{
    return vec3(componentes[0] - v.componentes[0], componentes[1] - v.componentes[1], componentes[2] - v.componentes[2]);
}

inline vec3 vec3::operator*(float escalar) const
{
    return vec3(componentes[0] * escalar, componentes[1] * escalar, componentes[2] * escalar);
}

inline vec3 vec3::operator*(const vec3 &v) const
{
    // Produto ponto entre dois vetores
    return vec3(componentes[0] * v.componentes[0], componentes[1] * v.componentes[1], componentes[2] * v.componentes[2]);
}

inline vec3 vec3::operator/(const vec3 &v) const
{
    return vec3(componentes[0] / v.componentes[0], componentes[1] / v.componentes[1], componentes[2] / v.componentes[2]);
}

inline vec3 vec3::operator/(float escalar) const
{
    return vec3(componentes[0] / escalar, componentes[1] / escalar, componentes[2] / escalar);
}

// Implementação dos operadores de atribuição
inline vec3 &vec3::operator+=(const vec3 &v)
{
    componentes[0] += v.componentes[0];
    componentes[1] += v.componentes[1];
    componentes[2] += v.componentes[2];
    return *this;
}

inline vec3 &vec3::operator-=(const vec3 &v)
{
    componentes[0] -= v.componentes[0];
    componentes[1] -= v.componentes[1];
    componentes[2] -= v.componentes[2];
    return *this;
}

inline vec3 &vec3::operator*=(const vec3 &v)
{
    componentes[0] *= v.componentes[0];
    componentes[1] *= v.componentes[1];
    componentes[2] *= v.componentes[2];
    return *this;
}

inline vec3 &vec3::operator/=(const vec3 &v)
{
    componentes[0] /= v.componentes[0];
    componentes[1] /= v.componentes[1];
    componentes[2] /= v.componentes[2];
    return *this;
}

inline vec3 &vec3::operator*=(float escalar)
{
    componentes[0] *= escalar;
    componentes[1] *= escalar;
    componentes[2] *= escalar;
    return *this;
}

inline vec3 &vec3::operator/=(float escalar)
{
    componentes[0] /= escalar;
    componentes[1] /= escalar;
    componentes[2] /= escalar;
    return *this;
}

// Normalização do vetor
inline void vec3::normalizar()
{
    float comprimento_atual = comprimento();
    if (comprimento_atual > 0)
    {
        componentes[0] /= comprimento_atual;
        componentes[1] /= comprimento_atual;
        componentes[2] /= comprimento_atual;
    }
}

vec3 reflexão(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

// Dentro da classe vec3

#endif
