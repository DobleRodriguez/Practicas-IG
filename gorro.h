#ifndef GORRO_H_INCLUDED
#define GORRO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "objrevolucion.h"

class Gorro {
    private:
    Cilindro * base = nullptr;
    Cilindro * tope = nullptr;

    public:
    Gorro();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis);
} ;

#endif