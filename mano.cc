#include "mano.h"

Mano::Mano() {
    Material amarillo = Material
    (Tupla4f(0.9, 0.9, 0, 1),
    Tupla4f(0.6, 0.6, 0.5, 1),
    Tupla4f(0, 0, 0, 1),
    32);

    cilindro = new Cilindro(10, 1, 0.5);
    cilindro -> setColor(Tupla3f(1, 0.9, 0.2));
    cilindro -> setMaterial(amarillo);
    tetraedro = new Tetraedro();
    tetraedro -> setColor(Tupla3f(1, 0.9, 0.2));
    tetraedro -> setMaterial(amarillo);
}

void Mano::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glPushMatrix();
            glScalef(0.8, 0.4, 0.8);
            cilindro -> draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, 0, 0.15);
            glScalef(0.6, 0.6, 0.6);
            glRotatef(180, 1, 0, 0);
            //glTranslatef(0, -0.5, 0);
            tetraedro -> draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
    glPopMatrix();
}