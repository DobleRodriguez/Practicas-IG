#include "gorro.h"
#include "aux.h"
#include "cilindro.h"
#include "objrevolucion.h"

Gorro::Gorro() {
    base = new Cilindro(20, 1, 0.5, Y, false, false);
    //base = new Cilindro(20, 0.1, 0.5, Y, false, false);
    base -> setColor(Tupla3f(0.9, 0.9, 0.9));
    tope = new Cilindro(20, 1, 0.5);
    tope -> setColor(Tupla3f(0.8, 0.8, 0.8));

}

void Gorro::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
    glPushMatrix();
        glScalef(1, 0.1, 1);
        base -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0.1, 0);
        glScalef(1, 0.3, 1);
        tope -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
}