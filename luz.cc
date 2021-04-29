#include "aux.h"
#include "luz.h"


void Luz::activar() {
    glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, color_difuso);
    glLightfv(GL_LIGHT0 + id, GL_SPECULAR, color_especular);
    glLightfv(GL_LIGHT0 + id, GL_AMBIENT, color_ambiente);
    glLightfv(GL_LIGHT0 + id, GL_POSITION, posicion);
    glEnable(GL_LIGHT0 + id);
    encendida = true;
}

void Luz::desactivar() {
    glDisable(GL_LIGHT0 + id);
    encendida = false;
}

Tupla4f Luz::getPosicion() {
    return posicion;
}

bool Luz::getEncendida() {
    return encendida;
}
