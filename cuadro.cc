#include "aux.h"
#include "malla.h"
#include "cuadro.h"
#include "textura.h"

Cuadro::Cuadro(float lado) {

    // Centramos la base del cubo en el origen de coordenadas
    GLfloat s = lado/2;

    // Inicializar la tabla de vértices
    v = { 
        Tupla3f(-s, 0, 0),      // 0 | Izquierda inferior delantera
        Tupla3f(s, 0, 0),       // 1 | Derecha inferior delantera
        Tupla3f(-s, lado, 0),   // 2 | Izquierda superior delantera   
        Tupla3f(s, lado, 0),    // 3 | Derecha superior delantera
    };
     // Inicializar la tabla de triángulos
    f = { 
        // Cara delantera 
        Tupla3i(2, 0, 1),       // Color A       
        Tupla3i(1, 3, 2),       // Color B
     };

    // Inicializar la tabla de colores
}

void Cuadro::setTextura() {
    ct.push_back(Tupla2f(0, 0));
    ct.push_back(Tupla2f(1, 0));
    ct.push_back(Tupla2f(0, 1));
    ct.push_back(Tupla2f(1, 1));
}
