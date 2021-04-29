#include "aux.h"
#include "luz.h"
#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f &orientacion, const unsigned id, 
const Tupla4f & c_difuso, const Tupla4f & c_especular, const Tupla4f & c_ambiente) {
    color_difuso = c_difuso;
    color_especular = c_especular;
    color_ambiente = c_ambiente;
    
    glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, color_difuso);
    glLightfv(GL_LIGHT0 + id, GL_SPECULAR, color_especular);
    glLightfv(GL_LIGHT0 + id, GL_AMBIENT, color_ambiente);
    alpha = orientacion(0);
    beta = orientacion(1);
    calcularPosicion();
    this -> id = id;
}


void LuzDireccional::variarAnguloAlpha(float incremento) {
    alpha += incremento;
    calcularPosicion();
}

void LuzDireccional::variarAnguloBeta(float incremento) {
    beta += incremento;
    calcularPosicion();
}

void LuzDireccional::calcularPosicion() {
    posicion = Tupla4f(
        sin(alpha) * cos(beta),
        sin(alpha) * sin(beta),
        cos(alpha),
        0
    );
    glLightfv(GL_LIGHT0 + id, GL_POSITION, posicion);
}
