#include "panadero.h"

Panadero::Panadero() {
    cabeza = new Cabeza();
    cuerpo = new Cuerpo();
}

void Panadero::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
    cuerpo -> draw(modo_dibujado, ajedrez, modo_vis);
    glPushMatrix();
        glTranslatef(0, 4.4, 0);
        glScalef(0.8, 0.5, 0.8);
        cabeza -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
}

void Panadero::animar() {
    cuerpo -> mover_pieza(0.1 * multiplicador[0], 0, 45, -45);
    cuerpo -> mover_pieza(0.1 * multiplicador[1], 1, 45, -45);
    cuerpo -> mover_pieza(0.1 * multiplicador[2], 2, 10, -45);
    cuerpo -> mover_pieza(0.1 * multiplicador[3], 3, 10, -45);
    cabeza -> saltarGorro(0.0025 * multiplicador[4], 1, 0);
}

void Panadero::acelerar(bool frenar, unsigned indice_objeto) {
    multiplicador[indice_objeto] += pow(-1, frenar);
    if (multiplicador[indice_objeto] < 0) {
        multiplicador[indice_objeto] = 0;
    }
}

void Panadero::alterarGradoLibertad(unsigned indice_objeto, bool invertido) {
    if (indice_objeto < 4) {
        cuerpo -> mover_pieza(10 * pow(-1, invertido), indice_objeto, MAXFLOAT, -MAXFLOAT);
    } else { //if (indice_objeto == 4) {
        cabeza -> saltarGorro(0.1 * pow(-1, invertido), MAXFLOAT, 0);
    }
}

