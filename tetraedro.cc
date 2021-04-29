#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro() {

    // Separación entre vértices (contenido en cubo por defecto)
    float s = 1;

    // Inicializar la tabla de vértices
    v = {
        Tupla3f(-s, 0, s),         // 0 | Izquierda inferior delantera
        Tupla3f(s, 0, s),          // 1 | Derecha inferior delantera
        Tupla3f(0, 0, -s),         // 2 | Central inferior trasera
        Tupla3f(0, s, 0)   // 3 | Central superior 
    };

    // Inicializar la tabla de triángulos
    f = {
        // Base
        Tupla3i(0, 2, 1),
        // Caras laterales
        Tupla3i(3, 0, 1),
        Tupla3i(3, 1, 2),
        Tupla3i(3, 2, 0)
    };

}

