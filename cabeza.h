#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "objrevolucion.h"
#include "malla.h"
#include "gorro.h"

class Cabeza : public Malla3D {
    private:
    ObjRevolucion * cil_redondeado = nullptr;
    Cilindro * cilindro = nullptr;
    Gorro * gorro = nullptr;


    float salto_gorro = 0;
    bool cayendo = false;

    public:
    Cabeza();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis);
    void saltarGorro(float salto, float max_altura, float min_altura);
} ;

#endif