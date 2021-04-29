#include "aux.h"
#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float radio) {
    std::vector<Tupla3f> perfil_original;

    float alpha = 3 * M_PI / 2;
    for (GLuint i = 0; i < num_vert_perfil; i++) {
        perfil_original.push_back(Tupla3f(
            radio * cos(alpha - (i * (M_PI / (num_vert_perfil - 1)))),
            radio * sin(alpha - (i * (M_PI / (num_vert_perfil - 1)))) + radio,
            0
        ));
    }
    crearMalla(perfil_original, num_instancias_perf, true, true, Y);
};
