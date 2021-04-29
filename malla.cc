#include "aux.h"
#include "malla.h"
#include "textura.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato() {

  // Habilitar uso de arrays de componentes
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

  // Formato y dirección de memoria del array
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glNormalPointer(GL_FLOAT, 0, nv.data());
   glColorPointer(3, GL_FLOAT, 0, c.data());

  // Visualizar, indicando tipo de primitiva, # índices, típo indices y dirección de la tabla
   glDrawElements(GL_TRIANGLES, nro_f, GL_UNSIGNED_INT, f.data());
  
  // Deshabilitar array de vértices
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
void Malla3D::draw_ModoDiferido() {
   // Comprobar que los VBO existen. Si no, crear
   if (id_vbo_ver == 0) {
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * sizeof(Tupla3f), v.data());
   }
   if (id_vbo_tri == 0) {
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(Tupla3i), f.data());
   }
   if (id_vbo_norm == 0) {
      id_vbo_norm = CrearVBO(GL_ARRAY_BUFFER, nv.size() * sizeof(Tupla3f), nv.data());
   }

   // Especificar localización y formato de las tablas
   // Vértices
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // Activar VBO vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);        // Especificar formato y offset
   glBindBuffer(GL_ARRAY_BUFFER, 0);          // Desactivar VBO de vértices

   // Colores.
   switch (visualizacion) {
      case GL_FILL: 
      if (id_vbo_col_s == 0) {
         id_vbo_col_s = CrearVBO(GL_ARRAY_BUFFER, c.size() * sizeof(Tupla3f), c.data());
      }
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_s);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0); 
      break;

      case GL_LINE:
      if (id_vbo_col_l == 0) {
         id_vbo_col_l = CrearVBO(GL_ARRAY_BUFFER, c.size() * sizeof(Tupla3f), c.data());
      }
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_l);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0); 
      break;      

      case GL_POINT:
      if (id_vbo_col_p == 0) {
         id_vbo_col_p = CrearVBO(GL_ARRAY_BUFFER, c.size() * sizeof(Tupla3f), c.data());
      }
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col_p);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0); 
      break;

   }
   // Normales
   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_norm);
   glNormalPointer(GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // Habilitar tablas de componentes 
   glEnableClientState(GL_VERTEX_ARRAY); 
   glEnableClientState(GL_NORMAL_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // Visualizar triágulos con glDrawElements
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
   glDrawElements(GL_TRIANGLES, nro_f, GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   // Deshabilitar tablas de componentes
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {
   // Calcular normales
   if (nv.empty()) {
      calcularNormales();
   }

   m.aplicar();

   if (!ct.empty()) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }

   nro_f = f.size() * 3;
   // Determina modo de dibujado
   if (ajedrez && modo_vis == GL_FILL) {
      draw_ModoAjedrez();
   } else {
      setVisualizacion(modo_vis);
      switch (modo_dibujado) {
         case 1:
            draw_ModoInmediato();
            break;
         case 2:
            draw_ModoDiferido();
            break;
      }
   }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamano_bytes, GLvoid* puntero_ram) {

   // ID a generar. Valor de retorno
   GLuint id_vbo;

   // Generar VBO, recibir ID
   glGenBuffers(1, &id_vbo);

   // Activar VBO mediante ID
   glBindBuffer(tipo_vbo, id_vbo);

   // Transferir datos de RAM a GPU
   glBufferData(tipo_vbo, tamano_bytes, puntero_ram, GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo, 0);

   return id_vbo;
}

void Malla3D::calcularNormales() {
   
   // Rellenamos vector con tuplas vacías
   nv.assign(v.size(), Tupla3f(0,0,0));
   Tupla3f a,
           b,
           u;
   
   // Cálculos de vector normal de cara, se suma su valor normalizado
   // a cada uno de los vértices que lo conforman. Al finalizar el bucle
   // cada vértice tendrá la suma de todas las normales normalizadas de 
   // las caras que compone
   for(unsigned i = 0; i < f.size(); i++) {
      a = v[f[i](1)] - v[f[i](0)];
      b = v[f[i](2)] - v[f[i](0)];
      u =  a.cross(b);
      nv[f[i](0)] = u + nv[f[i](0)];
      nv[f[i](1)] = u + nv[f[i](1)];
      nv[f[i](2)] = u + nv[f[i](2)];
   }

   // Normalizamos los vectores normales de vértice
   for (Tupla3f i : nv) {
      i = i.normalized();
   }
}

void Malla3D::setMaterial(Material mat) {
   m = mat;
}

void Malla3D::setColor(Tupla3f color) {
   color_s = color;
}

void Malla3D::setVisualizacion(GLuint modo_vis) {
   glPolygonMode(GL_FRONT, modo_vis);
   visualizacion = modo_vis;
   c.clear();
   switch(modo_vis) {
      case GL_FILL:
      c.assign(v.size(), color_s);
      break;

      case GL_LINE:
      c.assign(v.size(), color_l);
      break;

      case GL_POINT:
      c.assign(v.size(), color_p);
      break;
   }
}

void Malla3D::draw_ModoAjedrez() {

   glPolygonMode(GL_FRONT, GL_FILL);
   std::vector<Tupla3i> f_par;
   std::vector<Tupla3i> f_impar;

   c.clear();
   c.assign(v.size(), Tupla3f(-1, -1, -1));

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, v.data());

   for (unsigned i = 0; i < nro_f / 3; i++) {
      if (i % 2 == 0) {
         f_par.push_back(f[i]);
         c[f[i](0)] = color_a1;
         c[f[i](1)] = color_a1;
         c[f[i](2)] = color_a1;
      }
   }
   glColorPointer(3, GL_FLOAT, 0, c.data());

   glDrawElements(GL_TRIANGLES, f_par.size() * 3, GL_UNSIGNED_INT, f_par.data());
   
   for (unsigned i = 0; i < nro_f / 3; i++) {
      if (i % 2 == 1) {
         c[f[i](0)] = color_a2;
         c[f[i](1)] = color_a2;
         c[f[i](2)] = color_a2;
         f_impar.push_back(f[i]);
      }
   }
   glColorPointer(3, GL_FLOAT, 0, c.data());

   glDrawElements(GL_TRIANGLES, f_impar.size() * 3, GL_UNSIGNED_INT, f_impar.data());

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);

}
