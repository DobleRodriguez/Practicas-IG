#include "textura.h"
#include "aux.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

Textura::Textura(std::string archivo) {

    glGenTextures(1, &textura_id);
    jpg::Imagen * pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    anchura = pimg -> tamX();
    altura = pimg -> tamY();

    texels = pimg -> leerPixels();
    using namespace std;
}

void Textura::activar() {
    glBindTexture(GL_TEXTURE_2D, textura_id);
    gluBuild2DMipmaps(GL_TEXTURE_2D,
                    GL_RGB,
                    anchura,
                    altura,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    texels);
    glEnable(GL_TEXTURE_2D);
}
