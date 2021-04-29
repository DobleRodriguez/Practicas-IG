#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "torso.h"
#include "brazo.h"
#include "pierna.h"

class Cuerpo {
   private:
   Torso * torso = nullptr;
   Brazo * brazo = nullptr;
   Pierna * pierna = nullptr;

    std::vector<float> angulos_piezas = {0, 0, 0, -45};
    std::vector<bool> movimiento_inverso = {false, true, false, false};
    // Brazo derecho[0]
    // Brazo izquierdo[1]
    // Pierna derecha[2]
    // Pierna izquierda[3]
    float angulo_brazos = 0;
    float angulo_pierna_izq = 0;
    float angulo_pierna_der = 0;
   float angulo_brazo = 90;
   float angulo_pierna = 45;

   public:
   Cuerpo();
   void draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis);  
   void mover_pieza(float angulo, int indice_pieza, float maximo = 360, float minimo = 0);
   void mover_piernas(float angulo, int indice_pieza, float maximo = 360, float minimo = 0);
} ;

#endif