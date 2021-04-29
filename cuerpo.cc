#include "cuerpo.h"

Cuerpo::Cuerpo() {
    torso = new Torso();
    brazo = new Brazo();
    pierna = new Pierna();
}

void Cuerpo::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
    glPushMatrix();
        //glScalef(1.3, 1.3, 1.3);
        glTranslatef(0, 1.9, 0);
        torso -> draw(modo_dibujado, ajedrez, modo_vis);
        glPushMatrix();
            glTranslatef(0, 2, 0);
                glPushMatrix();
                    glTranslatef(1.2, 0, 0);
                    glScalef(0.8, 1, 0.8);
                    glRotatef(angulos_piezas[0], 1, 0, 0);
                    brazo -> draw(modo_dibujado, ajedrez, modo_vis, false);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(-1.2, 0, 0);
                    glScalef(0.8, 1, 0.8);
                    glRotatef(angulos_piezas[1], 1, 0, 0);
                    brazo -> draw(modo_dibujado, ajedrez, modo_vis, true);
                glPopMatrix();
        glPopMatrix();
    //glPopMatrix();
    //glPushMatrix();
        //glTranslatef(2, 2, 0);
        //brazo -> draw(modo_dibujado, ajedrez, modo_vis, false);
        glTranslatef(0.5, 0, 0);
        glPushMatrix();
            glRotatef(angulos_piezas[2], 1, 0, 0);
            pierna -> draw(modo_dibujado, ajedrez, modo_vis, false);
            //glTranslatef(-0.5, 1.9, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-1, 0, 0);
            glRotatef(angulos_piezas[3], 1, 0, 0);
            pierna -> draw(modo_dibujado, ajedrez, modo_vis, true);
        glPopMatrix();
        //glTranslatef(0, 4, 0);
        //brazo -> draw(modo_dibujado, ajedrez, modo_vis, true);
    glPopMatrix();

}

void Cuerpo::mover_pieza(float angulo, int indice_pieza, float maximo, float minimo) {
    angulos_piezas[indice_pieza] += angulo * pow(-1, (int)movimiento_inverso[indice_pieza]);
    if (angulos_piezas[indice_pieza] >= maximo) {
        movimiento_inverso[indice_pieza] = true;
        angulos_piezas[indice_pieza] = maximo;
    }
    if (angulos_piezas[indice_pieza] <= minimo) {
        movimiento_inverso[indice_pieza] = false;
        angulos_piezas[indice_pieza] = minimo;
    }
}

