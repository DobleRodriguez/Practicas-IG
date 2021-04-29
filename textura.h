#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"

class Textura {
    GLuint textura_id = 0;
    unsigned char * texels;
    int anchura,
        altura;

    public:
        Textura(std::string archivo);
        void activar();

} ;

#endif