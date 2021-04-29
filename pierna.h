#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "cubo.h"

class Pierna : public Malla3D {
    private:
    Cilindro * cilindro = nullptr;
    Cubo * cubo = nullptr;
    Material mat;

    public:
    Pierna();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis, bool izquierda);

} ;

#endif