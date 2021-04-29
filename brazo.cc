#include "brazo.h"

Brazo::Brazo() {
    cilindro = new Cilindro(20, 1, 0.5);
    cilindro -> setColor(Tupla3f(0.9, 0.9, 0.9));
    esfera = new Esfera(10, 10, 0.5);
    esfera -> setColor(Tupla3f(0.9, 0.9, 0.9));
    mano = new Mano();

}

void Brazo::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis, bool izquierda) {
    glPushMatrix();
        //glTranslatef(0, 1.8, 0);
        glRotatef(pow(-1, izquierda)*30, 0, 0, 1);
        glRotatef(10, 1, 0, 0);
        glTranslatef(0, -0.5, 0);
        esfera -> draw(modo_dibujado, ajedrez, modo_vis);
        glTranslatef(0, -0.4, 0);
        glScalef(1, 0.9, 1);
        cilindro -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(pow(-1, izquierda)*0.45, -1, 0);
        glRotatef(-30, 1, 0, 0);
        glTranslatef(0, -0.4, 0);
        glScalef(0.8, 1, 0.8);
        cilindro -> draw(modo_dibujado, ajedrez, modo_vis);
        glTranslatef(0, -0.9, 0);
        mano -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
}

