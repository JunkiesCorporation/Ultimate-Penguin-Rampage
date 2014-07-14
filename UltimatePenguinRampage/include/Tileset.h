#ifndef TILESET_H
#define TILESET_H

#include "Texture.h"

class Tileset
{
    public:
        Tileset(); // Constructeur par défaut
        Tileset(int largeur, int hauteur, int largeurTiles, int hauteurTiles, std::string chemin); // Constructeur à utiliser

        ~Tileset(); // Destructeur

        void render(int tileID, int x, int y);
    protected:
    private:
        int m_largeur; // La largeur, en # de tiles
        int m_hauteur; // La hauteur, en # de tiles
        int m_largeurTiles; // La largeur d'une tile, en px
        int m_hauteurTiles; // La hauteur d'une tile, en px

        Texture m_image; // L'image du Tileset
};

#endif // TILESET_H
