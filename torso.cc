#include "torso.h"

Torso::Torso() {
    cubo = new Cubo();
    cubo -> setColor(Tupla3f(0.6, 0.6, 0.6));
    trapecio = new Trapecio();
    trapecio -> setColor(Tupla3f(0.9, 0.9, 0.9));
}

void Torso::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glScalef(2.4, 2, 0.4);
        trapecio -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
}