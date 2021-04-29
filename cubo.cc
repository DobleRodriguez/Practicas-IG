#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado) {

    // Centramos la base del cubo en el origen de coordenadas
    GLfloat s = lado/2;

    // Inicializar la tabla de vértices
    v = { 
        Tupla3f(-s, 0, s),      // 0 | Izquierda inferior delantera
        Tupla3f(s, 0, s),       // 1 | Derecha inferior delantera
        Tupla3f(-s, lado, s),   // 2 | Izquierda superior delantera   
        Tupla3f(s, lado, s),    // 3 | Derecha superior delantera
        Tupla3f(-s, 0, -s),     // 4 | Izquierda inferior trasera
        Tupla3f(s, 0, -s),      // 5 | Derecha inferior trasera
        Tupla3f(s, lado, -s),   // 6 | Derecha superior trasera
        Tupla3f(-s, lado, -s)   // 7 | Izquierda superior trasera
    };
     // Inicializar la tabla de triángulos
    f = { 
        // Cara delantera 
        Tupla3i(2, 0, 1),       // Color A       
        Tupla3i(1, 3, 2),       // Color B
        // Cara superior 
        Tupla3i(2, 3, 7),       // Color A
        Tupla3i(7, 3, 6),       // Color B
        // Cara lateral derecha
        Tupla3i(3, 1, 5),       // Color A
        Tupla3i(3, 5, 6),       // Color B
        // Cara inferior
        Tupla3i(1, 4, 5),       // Color A
        Tupla3i(4, 1, 0),       // Color B
        // Cara lateral izquierda
        Tupla3i(0, 7, 4),       // Color A
        Tupla3i(7, 0, 2),       // Color B
        // Cara trasera 
        Tupla3i(4, 6, 5),       // Color A 6 7 5
        Tupla3i(4, 7, 6)        // Color B 7 5 4
     };

}
