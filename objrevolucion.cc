#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <algorithm>




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************

ObjRevolucion::ObjRevolucion(){}

// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, const unsigned eje) {
    std::vector<Tupla3f> perfil_original;
    ply::read_vertices(archivo, perfil_original);
    crearMalla(perfil_original, num_instancias, tapa_sup, tapa_inf, eje);
}

// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, const unsigned eje) {
    crearMalla(archivo, num_instancias, tapa_sup, tapa_inf, eje);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf, const unsigned eje) {
    // Primero, comprobamos el orden en el que viene dado el perfil.
    // Para lidiar con casos de múltiples puntos a la misma altura
    // (que podría tener sentido en ciertos sólidos contenidos uno dentro de otro)
    // lo hacemos contenido en un for hasta que podemos determinar un orden
    // Si eso no pasa (es bidimensional) pues entonces podemos asumir que es 
    // ascendente (Pues no tiene ningún orden)
    GLuint num_vertices = perfil_original.size();
    for (GLuint i = 0; i < num_vertices; i++) {
        if (perfil_original[i](eje) != perfil_original[(i + 1) % num_vertices](eje)) {
            if (perfil_original[i](eje) > perfil_original[(i + 1) % num_vertices](eje)) {
                std::reverse(perfil_original.begin(), perfil_original.end());
            }
            break;
        }
    }
    Tupla3f polo_norte;
    Tupla3f polo_sur;
    
    // Detectamos tapa
    if (perfil_original[num_vertices - 1]((eje + 1) % num_ejes) == 0 && perfil_original[num_vertices - 1]((eje + 2) % num_ejes) == 0) {
        polo_norte = perfil_original[num_vertices - 1];
        perfil_original.erase(perfil_original.end() - 1);
        num_vertices--;
        tapa_sup = true;
    // o la formamos
    } else if (tapa_sup) {
        polo_norte = Tupla3f();
        polo_norte(eje) = perfil_original[num_vertices - 1](eje);
        polo_norte((eje + 1) % num_ejes) = 0;
        polo_norte((eje + 2) % num_ejes) = 0;
    }

    // Ídem para el polo sur
    if (perfil_original[0]((eje + 1) % num_ejes) == 0 && perfil_original[0]((eje + 2) % num_ejes) == 0) {
        polo_sur = perfil_original[0];
        perfil_original.erase(perfil_original.begin());
        num_vertices--;
        tapa_inf = true;
    } else if (tapa_inf) {
        polo_sur = Tupla3f();
        polo_sur(eje) = perfil_original[0](eje);
        polo_sur((eje + 1) % num_ejes) = 0;
        polo_sur((eje + 2) % num_ejes) = 0;
    }


    // Seguimos el procedimiento del guión. 
    Tupla3f vertice_rotado;
    std::vector<std::vector<Tupla3f>> matriz_rotacion;
    float alpha;

    // Para cada instancia de cada vértice
    for (GLuint i = 0; i < num_instancias; i++) { // <=
        Tupla3f vert_duplicado;
        for (GLuint j = 0; j < num_vertices; j++) {
            // Determinamos los valores de rotación
            alpha = 2*M_PI*i / num_instancias;
            matriz_rotacion.insert(matriz_rotacion.begin(), {
                Tupla3f(1, 0, 0),
                Tupla3f(0, cos(alpha), sin(alpha)),
                Tupla3f(0, -sin(alpha), cos(alpha))
            });
            matriz_rotacion.insert(matriz_rotacion.begin() + 1,{
                Tupla3f(cos(alpha), 0, -sin(alpha)),
                Tupla3f(0, 1, 0),
                Tupla3f(sin(alpha), 0, cos(alpha))
            });
            matriz_rotacion.insert(matriz_rotacion.begin() + 2,{
                Tupla3f(cos(alpha), sin(alpha), 0),
                Tupla3f(-sin(alpha), cos(alpha), 0),
                Tupla3f(0, 0, 1)
            });
            // Insertamos el vértice rotado 
            v.push_back( 
                Tupla3f(
                    perfil_original[j].dot(matriz_rotacion[eje][0]),
                    perfil_original[j].dot(matriz_rotacion[eje][1]),
                    perfil_original[j].dot(matriz_rotacion[eje][2])
                )
            );
            /*
            if (j == 0) {
                vert_duplicado = Tupla3f(
                    perfil_original[j].dot(matriz_rotacion[eje][0]),
                    perfil_original[j].dot(matriz_rotacion[eje][1]),
                    perfil_original[j].dot(matriz_rotacion[eje][2])
                );
            }
            */
        }
        //v.push_back(vert_duplicado);
    }

    // Insertamos los triángulos
    float a,
          b;
    for (GLuint i = 0; i < num_instancias; i++) {
        for (GLuint j = 0; j < num_vertices - 1; j++) {
            a = num_vertices * i + j;
            b = num_vertices * ((i + 1) % num_instancias) + j;
            f.push_back(Tupla3i(a, b + 1, b ));
            f.push_back(Tupla3i(a, a + 1, b + 1));
        }
    }

    unsigned f_sin_tapas = f.size();
    // Insertamos, de ser solicitados, las tapas. Para ello
    if (tapa_inf) {
        v.push_back(polo_sur);
        // Insertamos el vértice
        // Y construimos los triángulos que conectan el primer vértice
        // de cada instancia con el polo
        for (unsigned i = 0; i < num_instancias; i++) {
            f.push_back(
                Tupla3i(
                    num_instancias * num_vertices, 
                    num_vertices * i,
                    num_vertices * ((i + 1) % num_instancias) 
                )
            ); 
        }
    }

    // Ídem pero con el polo norte y las últimas tapas
    if (tapa_sup) {
        v.push_back(polo_norte);
        for (unsigned i = 0; i < num_instancias; i++) {
            f.push_back(
                Tupla3i(
                    num_vertices * (i + 1) - 1,
                    num_instancias * num_vertices + 1, 
                    num_vertices * (((i + 1) % num_instancias) + 1) - 1
                )
            );
        }
    }
    f_tapas = f.size() - f_sin_tapas;
}

void ObjRevolucion::draw(GLuint modo_dibujado, bool ajedrez, GLuint modo_vis) {

   // Aplicar materiales. Solo en modo iluminado?
   m.aplicar();

   // Calcular normales
   if (nv.empty()) {
      calcularNormales();
   }

    //std::cout << f_tapas << " + " << sin_tapas << std::endl;
   nro_f = (f.size() - (f_tapas * sin_tapas)) * 3;
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

void ObjRevolucion::quitarTapas() {
    sin_tapas = !sin_tapas;
}




