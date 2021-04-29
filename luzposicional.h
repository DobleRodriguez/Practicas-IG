#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz {
    public:
    LuzPosicional(const Tupla3f & posicion, const unsigned id, const Tupla4f & c_difuso, 
const Tupla4f & c_especular, const Tupla4f & c_ambiente);
} ;

#endif