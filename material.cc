#include "material.h"
#include "aux.h"

Material::Material() {}
Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo) {
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;
    this -> brillo = brillo;
}

void Material::aplicar() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);
}