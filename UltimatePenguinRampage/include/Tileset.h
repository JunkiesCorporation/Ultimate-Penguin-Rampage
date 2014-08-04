#ifndef TILESET_H
#define TILESET_H

#include "Texture.h"
#include "Enums.h"
#include "Struct.h"

class Tileset
{
    public:
        Tileset(); // Constructeur par défaut
        Tileset(std::string cheminFichier); // Constructeur à utiliser

        ~Tileset(); // Destructeur

        void render(int tileID, int x, int y) const; ///< Affiche la tile demandée - x et y en pixel
        bool isTileSolide(int tileID) const;

        int getLargeurTiles() const; ///< Getter : retourne m_largeurTiles
        int getHauteurTiles() const; ///< Getter : retourne m_hauteurTiles
    protected:
    private:
        /// Permet de charger le Tileset
        void charger(std::string cheminImage); // Charge le tileset dans un tableau de tiles;

        int m_largeur; ///< La largeur, en # de tiles
        int m_hauteur; ///< La hauteur, en # de tiles
        int m_largeurTiles; ///< La largeur d'une tile, en px
        int m_hauteurTiles; ///< La hauteur d'une tile, en px
        Tile *m_tiles; ///< Tableau contenant tous les tiles du Tileset
        Texture m_image; ///< L'image du Tileset
};

#endif // TILESET_H
