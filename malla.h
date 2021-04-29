// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D {
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(GLuint modo_dibujado, bool ajedrez, GLuint visualizacion) ;

   void draw_ModoAjedrez();

   void setVisualizacion(GLuint modo_vis);
   void setMaterial(Material mat);
   void setColor(Tupla3f color);


   // GLuint modoDibujado = 2;   // Por defecto se dibuja en modo diferido
       
   protected:

   void calcularNormales() ; // calcula tabla de normales de vértices (práctica 3)

   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3f> v ;  

   // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f ; 

   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> c;
   std::vector<Tupla3f> ca;

   std::vector<Tupla3f> nv;

   std::vector<Tupla2f> ct;

   Material m = Material(Tupla4f(0.9, 0.9, 0.9, 1),
                         Tupla4f(0.9, 0.9, 0.9, 1),
                         Tupla4f(0.1, 0.1, 0.1, 1),
                         32);

   Tupla3f color_s = Tupla3f(0.5, 0.5, 0.5);
   Tupla3f color_l = Tupla3f(0.4, 0, 0.8);
   Tupla3f color_p = Tupla3f(1, 0.2, 0);
   Tupla3f color_a1 = Tupla3f(0, 0.8, 0.4);
   Tupla3f color_a2 = Tupla3f(0.8, 0.6, 0);

   GLuint visualizacion;

   unsigned nro_f;

   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   GLuint id_vbo_ver = 0;     // Identificador de buffer de vértices
   GLuint id_vbo_tri = 0;     // Identificador de buffer de triángulos
   GLuint id_vbo_col_s = 0;
   GLuint id_vbo_col_l = 0;
   GLuint id_vbo_col_p = 0;
   GLuint id_vbo_norm = 0;     // Identificador de buffer de colores
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamano_bytes, GLvoid* puntero_ram);
} ;


#endif
