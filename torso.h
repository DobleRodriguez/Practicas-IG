#ifndef TORSO_H_INCLUDED
#define TORSO_H_INCLUDED

#include "aux.h"
#include "cubo.h"
#include "trapecio.h"

class Torso  {
    private:
    Cubo * cubo = nullptr;
    Trapecio * trapecio = nullptr;
    public:
    Torso();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis);
} ;

#endif