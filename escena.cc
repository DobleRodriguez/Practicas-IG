
#include <algorithm>
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "textura.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************


 // TO_DO:
 // Refactorizar modo ajedrez
 // Control de tapas (para que sea de ObjRevolucion solamente)
 // Visualizacion múltiple ?
 // La normalización no se está guardando en nv ??????

Escena::Escena() {
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );


    luces.assign(8, nullptr);// = std::vector<Luz *>(8, nullptr);
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    cilindro = new Cilindro(21, 1, 0.5);
    cono = new Cono(20, 1, 0.5);
    esfera = new Esfera(20, 20, 1);
    ply = new ObjPLY("./plys/big_dodge.ply");
    objRev = new ObjRevolucion("./plys/peon.ply", 20, true, true);
    rectangulo = new Rectangulo(3, 0.01);

    cuadro_pared = new Cuadro();
    cuadro_pared -> setColor(Tupla3f(1, 1, 1));
    cuadro_pared -> setTextura();
    cuadro_suelo = new Cuadro();
    cuadro_suelo -> setColor(Tupla3f(1, 1, 1));
    cuadro_suelo -> setTextura();
    cuadro_pared2 = new Cuadro();
    cuadro_pared2 -> setColor(Tupla3f(1, 1, 1));
    cuadro_pared2 -> setTextura();
    cuadro_techo = new Cuadro();
    cuadro_techo -> setColor(Tupla3f(1, 1, 1));
    hormiga = new ObjPLY("./plys/ant.ply");
    hormiga -> setColor(Tupla3f(0.1, 0.1, 0.1));
    hormiga -> setMaterial(Material(
        Tupla4f(0.1, 0.1, 0.1, 1),
        Tupla4f(0.9, 0.9, 0.9, 1),
        Tupla4f(0, 0, 0, 1),
        51.2
    ));


    tex_madera = new Textura("./texturas/text-madera.jpg");
    tex_ladrillo = new Textura("./texturas/text-ladrillo.jpg");
    tex_horno = new Textura("./texturas/text-horno.jpg");
    tex_puerta = new Textura("./texturas/text-puerta.jpg");

    modelo_jerarquico = new Panadero();
    lampara = new Cono(10, 1, 0.5);
    repisa = new Cubo();
    repisa -> setColor(Tupla3f(0.5, 0.5, 0.5));
    repisa -> setMaterial(Material(
        Tupla4f(0.5, 0.5, 0.5, 1),
        Tupla4f(0.5, 0.5, 0.5, 1),
        Tupla4f(0.2, 0.2, 0.2, 1),
        51.2
    ));

    pan = new Esfera(10, 10, 0.5);
    pan -> setColor(Tupla3f(0.7, 0.5, 0));
    pan -> setMaterial(Material(
        Tupla4f(0.15, 0.1, 0, 1),
        Tupla4f(0.93, 0.75, 0.48, 1),
        Tupla4f(0, 0, 0, 1),
        32
    )) ;

    peon = new ObjRevolucion("./plys/peon.ply", 20, true, true);
    peon -> setColor(Tupla3f(0.9, 0.9, 0.9));
    peon -> setMaterial(Material(
        Tupla4f(0.9, 0.9, 0.9, 1),
        Tupla4f(0.05, 0.05, 0.05, 1),
        Tupla4f(0.2, 0.2, 0.2, 1),
        2
    ));



    luces[0] = new LuzDireccional(Tupla2f(0.3, 0.3), 0, Tupla4f(0.8, 0.8, 0.8, 1),
    Tupla4f(1, 1, 1, 1), Tupla4f(0.2, 0.2, 0.2, 1));
    luces[1] = new LuzPosicional(Tupla3f(0, 10, -2), 1, Tupla4f(0.5, 0.325, 0, 1),
    Tupla4f(0.3, 0.3, 0.2, 1), Tupla4f(0, 0, 0, 1));
    luces[2] = new LuzPosicional(Tupla3f(0, 10, 2), 2, Tupla4f(0.5, 0.325, 0, 1),
    Tupla4f(0.3, 0.3, 0.2, 1), Tupla4f(0, 0, 0, 1));
    
}


//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height ) {
    // Flags de entrada
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

    glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

    Width  = UI_window_width/10;
    Height = UI_window_height/10;

    change_projection( float(UI_window_width)/float(UI_window_height) );
    glViewport( 0, 0, UI_window_width, UI_window_height );

}

void Escena::animarModeloJerarquico() {
    if (animacion_automatica) {
        modelo_jerarquico -> animar();
    }
}


// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar() {
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    glDisable(GL_LIGHTING);
    change_observer();
    ejes.draw();
    
    int i = 0,
        j = 0,
        k = 0,
        l = 0,
        factor_desp = 2;

    glScalef(20, 20, 20);
    glShadeModel(suavizado);

    if (luces_activadas) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }

    if (figuras.empty() && fig_revs.empty()) {
        for (GLuint i : modosVis) {
           // panadero -> setVisualizacion(i);
            //modelo_jerarquico -> draw(modo_dibujado, ajedrez, i);
            glPushMatrix();
                glTranslatef(0, 14, -2);
                //lampara -> draw(modo_dibujado, ajedrez, i);
                glTranslatef(0, 0, +4);
                //lampara -> draw(modo_dibujado, ajedrez, i);
            glPopMatrix();
        }
        glPushMatrix();
            glTranslatef(0, 5, -7.5);
            glScalef(15, 0.5, 5);
            //repisa -> draw(modo_dibujado, ajedrez, i);
            glTranslatef(0, 5, 0);
            //repisa -> draw(modo_dibujado, ajedrez, i);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(1, 0, 0);
            //glTranslatef(1, 6, -8);
            glScalef(0.1, 0.1, 0.1);
            hormiga -> draw(modo_dibujado, ajedrez, i);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3, 5.5, -6.5);
            glScalef(2.3, 1, 2.3);
            //pan -> draw(modo_dibujado, ajedrez, i);
            glTranslatef(3, 0, 0);
            //pan -> draw(modo_dibujado, ajedrez, i);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1, 0, 0);
            //glTranslatef(-3, 9.5, -6.5);
            peon -> draw(modo_dibujado, ajedrez, i);
        glPopMatrix();



        tex_madera -> activar();
        glPushMatrix();
            glScalef(20, 20, 20);
            glPushMatrix();
                glRotatef(270, 1, 0, 0);
                glTranslatef(0, -0.5, 0);
                //cuadro_suelo -> draw(modo_dibujado, ajedrez, GL_FILL);
            glPopMatrix();
            tex_ladrillo -> activar();
            glPushMatrix();
                glTranslatef(0, 0, -0.5);
                //cuadro_pared -> draw(modo_dibujado, ajedrez, GL_FILL);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0, 0, 0.5);
                glRotatef(180, 0, 1, 0);
                //cuadro_pared -> draw(modo_dibujado, ajedrez, GL_FILL);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.5, 0.5, 0);
                glRotatef(270, 0, 1, 0);
                glRotatef(180, 0, 0, 1);
                glTranslatef(0, -0.5, 0);
                //cuadro_pared -> draw(modo_dibujado, ajedrez, GL_FILL);
            glPopMatrix();
            tex_horno -> activar();
            glPushMatrix();
                glTranslatef(-0.5, 0.5, 0);
                glRotatef(90, 0, 1, 0);
                glRotatef(180, 0, 0, 1);
                glTranslatef(0, -0.5, 0);
                //cuadro_pared2 -> draw(modo_dibujado, ajedrez, GL_FILL);
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glTranslatef(0, 1, 0);
                glRotatef(90, 1, 0, 0);
                glTranslatef(0, -0.5, 0);
                //cuadro_techo -> draw(modo_dibujado, ajedrez, GL_FILL);
            glPopMatrix();
                
        glPopMatrix();
    }

    // Si no existe figura, pintar escena
    /*if (figuras.empty() && fig_revs.empty()) {
        Material morado = Material(
            Tupla4f(1, 0, 1, 1.0),
            Tupla4f(0.6, 0.6, 0.5, 1.0),
            Tupla4f(1, 0, 1, 1.0),
            0.25 * 128
        );
        glPushMatrix();
        glTranslatef(0, 0, 1);
        cuadro -> setColor(Tupla3f(1, 1, 1));
        cuadro -> setMaterial(Material(Tupla4f(0.2, 0.2, 0.2, 1), 
        Tupla4f(0.7, 0.7, 0.7, 1), Tupla4f(0.8, 0.8, 0.8, 1), 40));
        cuadro -> setTextura();
        textura -> activar();
        cuadro -> draw(modo_dibujado, ajedrez);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1, 0, 0);
        objRev -> setColor(Tupla3f(1.0, 1.0, 1.0));
        objRev -> setMaterial(Material(
            Tupla4f(1.0, 1.0, 1.0, 1.0),
            Tupla4f(0.0, 0.0, 0.0, 1.0),
            Tupla4f(1, 1, 1, 1.0),
            0.0
        ));
        objRev -> draw(modo_dibujado, ajedrez);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-1, 0, 0);
        objRev -> setColor(Tupla3f(0.0, 0.0, 0.0));
        objRev -> setMaterial(Material(
            Tupla4f(0.1, 0.1, 0.1, 1.0),
            Tupla4f(1.0, 1.0, 1.0, 1.0),
            Tupla4f(0.0, 0.0, 0.0, 1.0),
            64
        ));
        glDisable(GL_TEXTURE_2D);
        objRev -> draw(modo_dibujado, ajedrez);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 1, 0);
        esfera -> setColor(Tupla3f(1.0, 0.55, 0.0));
        esfera -> setMaterial(morado);
        esfera -> draw(modo_dibujado, ajedrez);
        glPopMatrix();
    } else {*/

    for (Malla3D * figura : figuras) {
        glPushMatrix();
        glTranslatef(i, j, k);
        i += factor_desp;
        
        for (GLuint i : modosVis) {
            //figura -> setVisualizacion(i);
            figura -> draw(modo_dibujado, ajedrez, i);
        }
        glPopMatrix();
    }

    for (ObjRevolucion * figura : fig_revs) {
        glPushMatrix();
        glTranslatef(i, j, k);
        i += factor_desp;
        
        for (GLuint i : modosVis) {
            //figura -> setVisualizacion(i);
            figura -> draw(modo_dibujado, ajedrez, i);
        }
        glPopMatrix();
    }
    //}
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y ) {
    using namespace std ;
    cout << "Tecla pulsada: '" << tecla << "'" << endl;
    bool salir=false;
    switch (modoMenu) {
        case NADA: {
            switch (toupper(tecla)) {
                case 'Q' :
                    salir = true;
                    break;
                case 'O' :
                    modoMenu = SELOBJETO;
                    break;
                case 'V' :
                    modoMenu = SELVISUALIZACION;
                    break;
                case 'D' :
                    modoMenu = SELDIBUJADO;
                    break;
                case 'A' :
                    animacion_automatica = !animacion_automatica;
                    modoMenu = SELANIMAUTO;
                    break;
                case 'M' :
                    animacion_automatica = false;
                    modoMenu = SELANIMMANUAL;
                    break;
                default:
                    std::cout << "Opción inválida" << endl;
                    break;
            }
            break;
        }
        
        case SELOBJETO: {
            set<Malla3D *>::iterator it_malla3d;
            set<ObjRevolucion *>::iterator it_objrev;
            Malla3D * figura = nullptr;
            ObjRevolucion * fig_rev = nullptr;
            switch (toupper(tecla)) {
                case 'C' : // Cubo
                    figura = cubo;
                    break;
                case 'T' : // Tetraedro
                    figura = tetraedro;
                    break;
                case 'E' : // Esfera
                    fig_rev = esfera;
                    break;
                case 'R' : // cilindRo
                    fig_rev = cilindro;
                    break;
                case 'N' : // coNo
                    fig_rev = cono;
                    break;
                case 'Y' : // plY
                    figura = ply;
                    break;
                case 'J' : // obJrev
                    fig_rev = objRev;
                    break;
                case 'Q' : // Quit
                    modoMenu = NADA;
                    break;
                default:
                    std::cout << "Opción inválida" << endl;
                    break;
            }
            if (figura != nullptr) {
                it_malla3d = figuras.find(figura);
                if (it_malla3d == figuras.end()) {
                    figuras.insert(figura);
                } else {
                    figuras.erase(figura);
                }
            } else if (fig_rev != nullptr) {
                it_objrev = fig_revs.find(fig_rev);
                if (it_objrev == fig_revs.end()) {
                    fig_revs.insert(fig_rev);
                } else {
                    fig_revs.erase(fig_rev);
                }
            }
            break;
        }

        case SELVISUALIZACION: {

            set<GLuint>::iterator it_modovis;
            GLenum modo_visualizacion;
            switch(toupper(tecla)) {
                case 'P' : // Puntos
                    luces_activadas = false;
                    it_modovis = modosVis.find(GL_POINT);
                    if (it_modovis == modosVis.end()) {
                        modosVis.insert(GL_POINT);
                    } else {
                        modosVis.erase(GL_POINT);
                    }
                    break;

                case 'L' : // Líneas
                    luces_activadas = false;
                    it_modovis = modosVis.find(GL_LINE);
                    if (it_modovis == modosVis.end()) {
                        modosVis.insert(GL_LINE);
                    } else {
                        modosVis.erase(GL_LINE);
                    }
                    break;
                
                case 'S' : // Sólido
                    luces_activadas = false;
                    it_modovis = modosVis.find(GL_FILL);
                    if (it_modovis == modosVis.end()) {
                        modosVis.insert(GL_FILL);
                        ajedrez = false;
                    } else {
                        if (!ajedrez) {
                            modosVis.erase(GL_FILL);
                        } else {
                            ajedrez = false;
                        }
                    }
                    break;

                case 'A' : // Ajedrez
                    if (!luces_activadas) {
                        it_modovis = modosVis.find(GL_FILL);
                        if (it_modovis == modosVis.end()) {
                            modosVis.insert(GL_FILL);
                            ajedrez = true;
                        } else {
                            if (ajedrez) {
                                modosVis.erase(GL_FILL);
                            } else {
                                ajedrez = true;
                            }
                        }
                    } else {
                        var_alpha = true;
                        var_beta = false;
                    }
                    break;

                case 'T': // Tapas
                    for (ObjRevolucion * figura : fig_revs) {
                        figura -> quitarTapas();
                    }
                    break;

                case 'Z': // suaviZado
                    //std::cout << suavizado << std::endl;
                    if (suavizado == GL_FLAT) {
                        suavizado = GL_SMOOTH;
                    } else {
                        suavizado = GL_FLAT;
                    }
                    break;


                case 'I' : // Iluminación
                    luces_activadas = !luces_activadas;
                    for (Luz * luz : luces) {
                        if (luz != nullptr && luz -> getEncendida()) {
                            luz -> activar();
                        }
                    }
                    //modoMenu = SELILUMINACION;
                    break;

                case '0' :
                    if (luces_activadas && luces[0] != nullptr) {
                        if (luces[0] -> getEncendida()) {
                            luces[0] -> desactivar();
                        } else {
                            luces[0] -> activar();
                        }
                    }
                    break;
                case '1' :
                    if (luces_activadas && luces[1] != nullptr) {
                        if (luces[1] -> getEncendida()) {
                            luces[1] -> desactivar();
                        } else {
                            luces[1] -> activar();
                        }
                    }
                    break;
                case '2' :
                    if (luces_activadas && luces[2] != nullptr) {
                        if (luces[2] -> getEncendida()) {
                            luces[2] -> desactivar();
                        } else {
                            luces[2] -> activar();
                        }
                    }
                    break;
                case '3' :
                    if (luces_activadas && luces[3] != nullptr) {
                        if (luces[3] -> getEncendida()) {
                            luces[3] -> desactivar();
                        } else {
                            luces[3] -> activar();
                        }
                    }
                    break;
                case '4' :
                    if (luces_activadas && luces[4] != nullptr) {
                        if (luces[4] -> getEncendida()) {
                            luces[4] -> desactivar();
                        } else {
                            luces[4] -> activar();
                        }
                    }
                    break;
                case '5' :
                    if (luces_activadas && luces[5] != nullptr) {
                        if (luces[5] -> getEncendida()) {
                            luces[5] -> desactivar();
                        } else {
                            luces[5] -> activar();
                        }
                    }
                    break;
                case '6' :
                    if (luces_activadas && luces[6] != nullptr) {
                        if (luces[6] -> getEncendida()) {
                            luces[6] -> desactivar();
                        } else {
                            luces[6] -> activar();
                        }
                    }
                    break;
                case '7' :
                    if (luces_activadas && luces[7] != nullptr) {
                        if (luces[7] -> getEncendida()) {
                            luces[7] -> desactivar();
                        } else {
                            luces[7] -> activar();
                        }
                    }
                    break;

                case 'B' :
                    if (luces_activadas) {
                        var_alpha = false;
                        var_beta = true;
                    }
                    break;

                case '<' :
                    if (luces_activadas) {
                        if (var_alpha || var_beta) {
                            for (Luz* i : luces) {
                                if (i != nullptr && i -> getPosicion()(3) == 0) {
                                    if (var_alpha) {
                                        static_cast<LuzDireccional *>(i) -> variarAnguloAlpha(-incremento_angulo);
                                    } else if (var_beta) {
                                        static_cast<LuzDireccional *>(i) -> variarAnguloBeta(-incremento_angulo);                              
                                    }
                                }
                            }
                        }
                    }
                    break;
                case '>' :
                    if (luces_activadas) {
                        if (var_alpha || var_beta) {
                            for (Luz* i : luces) {
                                if (i != nullptr && i -> getPosicion()(3) == 0) {
                                    if (var_alpha) {
                                        static_cast<LuzDireccional *>(i) -> variarAnguloAlpha(incremento_angulo);
                                    } else if (var_beta) {
                                        static_cast<LuzDireccional *>(i) -> variarAnguloBeta(incremento_angulo);                              
                                    }
                                }
                            }
                        }
                    }
                    break;

                case 'Q' : // Quit
                    modoMenu = NADA;
                    break;

                default:
                    std::cout << "Opción inválida" << endl;
                    break;

                }
                dibujar();
            
            break;
        }

        case SELDIBUJADO: {
            switch(toupper(tecla)) {
                case '1' :
                    modo_dibujado = 1;
                    break;
                case '2' :
                    modo_dibujado = 2;
                    break;
                case 'Q' :
                    modoMenu = NADA;
                    break;
                default:
                    std::cout << "Opción inválida" << endl;
                    break;
            }
            dibujar();
            break;
        }

        case SELANIMAUTO: {
            switch(toupper(tecla)) {
                case '0' :
                    grado_libertad_seleccionado = 0;
                    break;

                case '1' :
                    grado_libertad_seleccionado = 1;
                    break;

                case '2' :
                    grado_libertad_seleccionado = 2;
                    break;

                case '3' :
                    grado_libertad_seleccionado = 3;
                    break;

                case '4' :
                    grado_libertad_seleccionado = 4;
                    break;

                case '+' :
                    if (grado_libertad_seleccionado == -1) {
                        for (unsigned i = 0; i < nro_grados_libertad; i++) {
                            modelo_jerarquico -> acelerar(false, i);
                        }
                    } else {
                        modelo_jerarquico -> acelerar(false, grado_libertad_seleccionado);
                    }
                    break;
                case '-' :
                    if (grado_libertad_seleccionado == -1) {
                        for (unsigned i = 0; i < nro_grados_libertad; i++) {
                            modelo_jerarquico -> acelerar(true, i);
                        }
                    } else {
                        modelo_jerarquico -> acelerar(true, grado_libertad_seleccionado);
                    }
                    break;
                case 'A' :
                    animacion_automatica = false;
                    grado_libertad_seleccionado = -1;
                    modoMenu = NADA;
                    break;
                default:
                    std::cout << "Opción inválida" << endl;
                    break;
            }
            break;
        }

        case SELANIMMANUAL: {
            switch(toupper(tecla)) {
                case '0' :
                    grado_libertad_seleccionado = 0;
                    break;

                case '1' :
                    grado_libertad_seleccionado = 1;
                    break;

                case '2' :
                    grado_libertad_seleccionado = 2;
                    break;

                case '3' :
                    grado_libertad_seleccionado = 3;
                    break;

                case '4' :
                    grado_libertad_seleccionado = 4;
                    break;

                case '+' :
                    if (grado_libertad_seleccionado >= 0) {
                        modelo_jerarquico -> alterarGradoLibertad(grado_libertad_seleccionado, false);
                    }
                    break;

                case '-' :
                    if (grado_libertad_seleccionado >= 0) {
                        modelo_jerarquico -> alterarGradoLibertad(grado_libertad_seleccionado, true);
                    }
                    break;

                case 'Q' :
                    grado_libertad_seleccionado = -1;
                    modoMenu = NADA;
                    break;
                    
                default:
                    std::cout << "Opción inválida" << endl;
                    break;
            }
            break;
        }
    }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y ) {
    switch ( Tecla1 )
    {
	    case GLUT_KEY_LEFT:
        Observer_angle_y-- ;
        break;

        case GLUT_KEY_RIGHT:
        Observer_angle_y++ ;
        break;

        case GLUT_KEY_UP:
        Observer_angle_x-- ;
        break;

        case GLUT_KEY_DOWN:
        Observer_angle_x++ ;
        break;

        case GLUT_KEY_PAGE_UP:
        Observer_distance *=1.2 ;
        break;

        case GLUT_KEY_PAGE_DOWN:
        Observer_distance /= 1.2 ;
        break;
	}

}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
