#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "textura.h"

class Cuadro : public Malla3D {
   public:
   Cuadro(float l=1) ;
   void setTextura();
} ;






#endif
