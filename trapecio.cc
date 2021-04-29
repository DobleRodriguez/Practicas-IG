#include "aux.h"
#include "malla.h"
#include "trapecio.h"

Trapecio::Trapecio() {
    v = {
        Tupla3f(-0.5, 0, 1),      // Inferior izquierda frontal
        Tupla3f(0.5, 0, 1),       // Inferior derecha frontal
        Tupla3f(-0.3, 1, 1),      // Superior izquierda frontal
        Tupla3f(0.3, 1, 1),       // Superior derecha frontal
        Tupla3f(-0.5, 0, -1),     // Inferior izquierda trasera
        Tupla3f(0.5, 0, -1),      // Inferior derecha trasera
        Tupla3f(-0.3, 1, -1),     // Superior izquierda trasera
        Tupla3f(0.3, 1, -1)       // Superior derecha trasera
    } ;

    f = {
        // Frontal
        Tupla3i(1, 2, 0),
        Tupla3i(3, 2, 1),
        // Superior
        Tupla3i(3, 6, 2),
        Tupla3i(7, 6, 3),
        // Trasera
        Tupla3i(4, 6, 5),
        Tupla3i(6, 7, 5),
        // Inferior
        Tupla3i(0, 5, 1),
        Tupla3i(5, 0, 4),
        // Izquierda
        Tupla3i(0, 2, 6),
        Tupla3i(4, 0, 6),
        // Derecha
        Tupla3i(5, 3, 1),
        Tupla3i(3, 5, 7)
    } ;
}
