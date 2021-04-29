#include "aux.h"
#include "objrevolucion.h"
#include "cono.h"

Cono::Cono(int num_instancias_perf, float altura, float radio, unsigned eje, bool tapa_sup, bool tapa_inf) {

    std::vector<Tupla3f> perfil_original = {
        Tupla3f(radio, 0, 0),
        Tupla3f(0, altura, 0)
    } ;
    crearMalla(perfil_original, num_instancias_perf, tapa_sup, tapa_inf, eje);
    
};
