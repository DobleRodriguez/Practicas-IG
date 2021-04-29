#include "cabeza.h"

Cabeza::Cabeza() {
    Material amarillo = Material
    (Tupla4f(0.9, 0.9, 0, 1),
    Tupla4f(0.6, 0.6, 0.5, 1),
    Tupla4f(0, 0, 0, 1),
    32);

    std::vector<Tupla3f> perfil_cabeza;
    perfil_cabeza.push_back(Tupla3f(0.35, 0, 0));
    perfil_cabeza.push_back(Tupla3f(0.5, 0.2, 0));
    perfil_cabeza.push_back(Tupla3f(0.5, 1, 0));

    cil_redondeado = new ObjRevolucion(perfil_cabeza, 20);
    cil_redondeado -> setColor(Tupla3f(1, 0.9, 0.2));
    cil_redondeado -> setMaterial(amarillo);
    
    cilindro = new Cilindro(20, 1, 1);
    cilindro -> setColor(Tupla3f(1, 0.9, 0.2));
    cilindro -> setMaterial(amarillo);

    gorro = new Gorro();
}

void Cabeza::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
    glPushMatrix();
    glScalef(2, 2, 2);
        glPushMatrix();
            glScalef(0.3, 0.2, 0.3);
            cilindro -> draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, 0.85, 0);
            glScalef(0.3, 0.2, 0.3);
            cilindro -> draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
        glPushMatrix();
            glScalef(1, 0.7, 1);
            glTranslatef(0, 0.2, 0);
            cil_redondeado->draw(modo_dibujado, ajedrez, modo_vis);
            glTranslatef(0, 1 + salto_gorro, 0);
            glScalef(1, 2.5, 1);
            gorro -> draw(modo_dibujado, ajedrez, modo_vis);
        glPopMatrix();
    glPopMatrix();
}

void Cabeza::saltarGorro(float salto, float max_altura, float min_altura) {
    salto_gorro += salto * pow(-1, cayendo);
    if (salto_gorro >= max_altura) {
        salto_gorro = max_altura;
        cayendo = true;
    }
    if (salto_gorro <= min_altura) {
        salto_gorro = min_altura;
        cayendo = false;
    }
}