#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz {
    protected:
    float alpha,
          beta;
    void calcularPosicion();

    public:
    LuzDireccional(const Tupla2f &orientacion, const unsigned id, const Tupla4f & c_difuso, 
    const Tupla4f & c_especular, const Tupla4f & c_ambiente);
    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
} ;

#endif