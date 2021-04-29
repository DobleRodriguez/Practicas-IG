#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "esfera.h"
#include "mano.h"

class Brazo {
    private: 
    Cilindro * cilindro = nullptr;
    Esfera * esfera = nullptr;
    Mano * mano = nullptr;

    public:
    Brazo();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis, bool izquierda);
} ;

#endif