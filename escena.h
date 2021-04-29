#ifndef _ESCENA_H
#define _ESCENA_H

#include <set>
#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "rectangulo.h"
#include "cuadro.h"
#include "textura.h"
#include "panadero.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, SELANIMAUTO, SELANIMMANUAL} menu;
class Escena {

    private:

    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
        
        // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection( const float ratio_xy );
    void change_observer();



    void clear_window();

    menu modoMenu=NADA;
    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro = nullptr; // es importante inicializarlo a 'nullptr'
    Cilindro * cilindro = nullptr;
    Cono * cono = nullptr;
    Esfera * esfera = nullptr;
    ObjPLY * ply = nullptr;
    ObjRevolucion * objRev = nullptr;
    Rectangulo * rectangulo = nullptr;

    Cuadro * cuadro_pared = nullptr;
    Cuadro * cuadro_pared2 = nullptr;
    Cuadro * cuadro_pared3 = nullptr;
    Cuadro * cuadro_suelo = nullptr;
    Cuadro * cuadro_techo = nullptr;

    Panadero * modelo_jerarquico = nullptr;
    Cono * lampara = nullptr;
    Cubo * repisa = nullptr;
    Esfera * pan = nullptr;
    ObjPLY * hormiga = nullptr;
    ObjRevolucion * peon = nullptr;


    bool animacion_automatica = false;
    int grado_libertad_seleccionado = -1;
    unsigned nro_grados_libertad = 5;


    Textura * tex_madera = nullptr;
    Textura * tex_ladrillo = nullptr;
    Textura * tex_horno = nullptr;
    Textura * tex_pan = nullptr;
    Textura * tex_puerta = nullptr;

    // Contenedores de objetos
    std::set<Malla3D *> figuras;
    std::set<ObjRevolucion *> fig_revs;

    // Modo de visualización/dibujado
    std::set<GLuint> modosVis = {GL_FILL}; // Por defecto se dibuja en modo sólido
    bool ajedrez = false;
    GLuint modo_dibujado = 2;

    // Cuadro de luces
    std::vector<Luz *> luces;
    bool luces_activadas = false;
    GLenum suavizado = GL_SMOOTH;
    bool var_alpha = false;
    bool var_beta = false;
    const float incremento_angulo = 0.1;

    // Control de escena
    bool dibujar_escena = true;
    std::vector<Malla3D*> figuras_escena;

    bool test = true;

    public:

    Escena();
    void inicializar( int UI_window_width, int UI_window_height );
    void redimensionar( int newWidth, int newHeight ) ;
    void animarModeloJerarquico();

    // Dibujar
    void dibujar() ;

    // Interacción con la escena
    bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
    void teclaEspecial( int Tecla1, int x, int y );

};
#endif
