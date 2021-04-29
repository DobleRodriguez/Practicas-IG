#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
// #include "material.h"

class ObjRevolucion : public Malla3D {
    protected:
    const static unsigned
        X = 0,
        Y = 1,
        Z = 2,
        num_ejes = 3;
    bool sin_tapas = false;
    unsigned f_tapas = 0;

    public:
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias, bool 
    tapa_sup=true, bool tapa_inf=true, const unsigned eje = Y) ;
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool 
    tapa_sup=true, bool tapa_inf=true, const unsigned eje = Y) ;

    void quitarTapas();
    void draw(GLuint modo, bool ajedrez, GLuint modo_vis);
    
    protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, const int num_instancias, const bool tapa_sup, const bool tapa_inf, const unsigned eje);
    void calcularCoordTextura();
} ;

#endif
