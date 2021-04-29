#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz {
    protected:
    unsigned id;
    Tupla4f color_difuso;
    Tupla4f color_especular;
    Tupla4f color_ambiente;
    bool encendida = true;
    Tupla4f posicion;

    public:
    void activar();
    void desactivar();
    Tupla4f getPosicion();
    bool getEncendida();

} ;


#endif