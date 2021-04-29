#include "pierna.h"

Pierna::Pierna() {
    //cilindro = new Cilindro(20, 0.45, 0.2);
    mat = Material(
        Tupla4f(0, 0, 0.5, 1),
        Tupla4f(0.6, 0.6, 0.7, 1),
        Tupla4f(0, 0, 0, 1),
        32
    );
    cilindro = new Cilindro(20, 1, 0.5);// 0.45, 0.2);
    cilindro -> setColor(Tupla3f(0.1, 0.1, 0.6));
    cilindro -> setMaterial(mat);
    cubo = new Cubo();
    cubo -> setColor(Tupla3f(0.1, 0.1, 0.6));
    cubo -> setMaterial(mat);
}

void Pierna::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis, bool izquierda) {
    glPushMatrix();
        glTranslatef(0, 0, 0.125);
        glRotatef(90, 0, 0, 1);
        glScalef(1, 0.95, 1);
        glTranslatef(0, -0.5, 0);
        cilindro -> draw(modo_dibujado, ajedrez, modo_vis);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(pow(-1, izquierda) * 0.1, 0, 0);
        glPushMatrix();
            glTranslatef(0, -1.5, 0);
            glScalef(0.8, 2, 0.75);
            cubo->draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, -1.9, 0.125);
            glScalef(0.8, 0.4, 1);
            cubo -> draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
    glPopMatrix();

}