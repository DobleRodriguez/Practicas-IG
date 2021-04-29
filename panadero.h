#ifndef PANADERO_H_INCLUDED
#define PANADERO_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "cabeza.h"
#include "cuerpo.h"

class Panadero {
    private:
    Cabeza * cabeza = nullptr;
    Cuerpo * cuerpo = nullptr;
    std::vector<float> multiplicador = {5, 5, 5, 5, 5};

    public:
    Panadero();
    void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis);
    void animar();
    void acelerar(bool frenar, unsigned indice_objeto);
    void alterarGradoLibertad(unsigned indice_objeto, bool invertido);
} ;

#endif