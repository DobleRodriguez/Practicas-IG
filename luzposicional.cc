#include "aux.h"
#include "luz.h"
#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & posicion, const unsigned id, 
const Tupla4f & c_difuso, const Tupla4f & c_especular, const Tupla4f & c_ambiente) {
    using namespace std;
    cout << id << endl;
    color_difuso = c_difuso;
    color_especular = c_especular;
    color_ambiente = c_ambiente;
    glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, color_difuso);
    glLightfv(GL_LIGHT0 + id, GL_SPECULAR, color_especular);
    glLightfv(GL_LIGHT0 + id, GL_AMBIENT, color_ambiente);
   
    this->posicion = Tupla4f(posicion(X), posicion(Y), posicion(Z), 1);
    glLightfv(GL_LIGHT0 + id, GL_POSITION, posicion);

    this -> id = id;

}

