#include <iostream>
#include <fstream>
#include <cmath>
#include "esfera.h"
#include "hitable.h"
#include "lista_hitables.h"
#include "camera.h"
#include "material.h"
#include "limits"

// Função que gera a cor do pixel com base no raio
vec3 cor(const ray &r, hitable *world, int profundidade)
{
    hit_record rec;

    // Verifica se o raio atinge algum objeto no mundo
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        vec3 emitido = rec.mat_ptr->emitir(); // Obter emissão do material
        vec3 atenuacao;
        ray espalhado;

        // Se ainda temos profundidade para recursão e o material espalha luz
        if (profundidade > 0 && rec.mat_ptr->espalhamento(r, rec, atenuacao, espalhado))
        {
            // Soma a emissão com a cor obtida do próximo raio espalhado
            return emitido + atenuacao * cor(espalhado, world, profundidade - 1);
        }
        else
        {
            // Apenas retorna a emissão, sem espalhamento
            return emitido;
        }
    }
    else
    {
        // Gradiente de fundo representando o espaço
        float t = 0.5 * (r.direction().obter_y() + 1.0);                        // Normaliza a direção y
        vec3 fundo = (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0); // Gradiente de verde-azulado escuro para preto
        return fundo;                                                           // Retorna a cor de fundo                                                          // R
    }
}

int main()
{
    // Definindo a resolução da imagem
    int largura = 800;
    int altura = 400;
    int ns = 100;

    // Abre o arquivo para escrita
    std::ofstream arquivo("imagem.ppm");
    if (!arquivo)
    {
        std::cerr << "Erro ao criar o arquivo\n";
        return 1;
    }

    // Cabeçalho do arquivo PPM
    arquivo << "P3\n"
            << largura << " " << altura << "\n255\n";

    // Configuração da câmera
    vec3 lookfrom(0, 50, 0);                             // Posição da câmera por cima
    vec3 lookat(0, 0, 0);                                // Ponto para onde a câmera está olhando (centro)
    vec3 vup(0, 0, -1);                                  // Vetor "up"
    float vfov = 90.0;                                   // Campo de visão vertical
    float aspect_ratio = float(largura) / float(altura); // Proporção da tela

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio);

    hitable *list[2]; // Aumenta o tamanho da lista para incluir o anel
    float raio_do_sol = 20.0;

    // Sol
    material *sol_material = new emissive(vec3(1.0, 1.0, 0.0) * 10);   // Cor amarela brilhante
    list[0] = new esfera(vec3(-180, 0, 0), raio_do_sol, sol_material); // Sol no centro

    // Mercúrio
    // material *mercurio_material = new lambertian(vec3(0.9, 0.9, 0.9)); // Mercúrio (prata muito claro)
    // list[1] = new esfera(vec3(-55, 0, 0), (raio_do_sol * 0.0035) * 5, mercurio_material);

    // Vênus
    // material *venus_material = new lambertian(vec3(1.0, 1.0, 0.7)); // Vênus (amarelo muito claro)
    // list[2] = new esfera(vec3(-50, 0, 0), (raio_do_sol * 0.009) * 5, venus_material);

    // Terra
    // material *terra_material = new lambertian(vec3(0.6, 0.8, 1.0)); // Terra (azul bem claro com verde)
    // list[3] = new esfera(vec3(-45, 0, 0), (raio_do_sol * 0.0091) * 5, terra_material);

    // Marte
    // material *marte_material = new lambertian(vec3(1.0, 0.7, 0.7)); // Marte (vermelho muito claro)
    // list[4] = new esfera(vec3(-40, 0, 0), (raio_do_sol * 0.005) * 5, marte_material);

    // Júpiter
    // material *jupiter_material = new lambertian(vec3(1.0, 0.8, 0.4)); // Júpiter (laranja bem claro com marrom claro)
    // list[5] = new esfera(vec3(-34, 0, 0), (raio_do_sol * 0.1004), jupiter_material);

    // Saturno
    // material *saturno_material = new lambertian(vec3(1.0, 1.0, 0.8)); // Saturno (amarelo muito pálido)
    // list[6] = new esfera(vec3(-28, 0, 0), (raio_do_sol * 0.0836), saturno_material);

    // Urano
    // material *urano_material = new lambertian(vec3(0.7, 1.0, 1.0)); // Urano (azul muito claro)
    // list[7] = new esfera(vec3(-23, 0, 0), (raio_do_sol * 0.0364), urano_material);

    // Netuno
    // material *netuno_material = new lambertian(vec3(0.6, 0.7, 1.0)); // Netuno (azul muito claro)
    // list[8] = new esfera(vec3(-19, 0, 0), (raio_do_sol * 0.0354), netuno_material);

    // planeta terra grande ( usar depois, apague os outros plan planetas para fazer a comparação)
    material *terra_material2 = new lambertian(vec3(0.5, 0.7, 1.0));
    list[1] = new esfera(vec3(0.0, 0.0, 0.0), 25, terra_material2);

    hitable *world = new hitable_lista(list, 2);

    // Loop para gerar as cores (controlar o rgb da imagem)
    for (int y = altura - 1; y >= 0; y--)
    {
        for (int x = 0; x < largura; x++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                // Calcula as coordenadas da direção do raio para cada pixel
                float u = float(x + drand48()) / float(largura);
                float v = float(y + drand48()) / float(altura);
                ray r = cam.pegar_raio(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += cor(r, world, 100); // Ajuste a profundidade conforme necessário
            }
            col /= float(ns);
            col = vec3(sqrt(col.obter_x()), sqrt(col.obter_y()), sqrt(col.obter_z()));
            // Converte a cor para o formato pPM e escreve no arquivo
            int ir = static_cast<int>(255.99 * col.obter_x());
            int ig = static_cast<int>(255.99 * col.obter_y());
            int ib = static_cast<int>(255.99 * col.obter_z());

            arquivo << ir << " " << ig << " " << ib << "\n";
        }
    }

    arquivo.close();
    std::cout << "Arquivo 'imagem.ppm' gerado com sucesso!\n";

    // Libera memória alocada dinamicamente
    for (int i = 0; i < 2; i++)
    {
        delete list[2];
    }
    delete world;

    return 0;
}