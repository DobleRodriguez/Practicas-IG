#ifndef MANO_H_INCLUDED
#define MANO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "tetraedro.h"

class Mano {
    private:
    Cilindro * cilindro = nullptr;
    Tetraedro * tetraedro = nullptr;

    public:
    Mano();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis);

} ;

#endif