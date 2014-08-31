#ifndef CARTE_H
#define CARTE_H

#include <string>

#include "Tileset.h"

class Carte
{
    public:
        Carte(std::string); ///< Constructeur

        ~Carte(); ///< Destructeur

        void render(SDL_Rect camera) const; ///< Affiche la carte
        bool isTileSolide(int x, int y) const; ///< Vérifie si la tile à la position donnée est solide

        int getLargeur() const; ///< Retourne m_largeur
        int getHauteur() const; ///< Retourne m_hauteur
        Pos getPtDeDepart() const; ///< Retourne m_ptDeDepart
    protected:
    private:
        void charger(); ///< Lis le fichier associé à la carte

        int m_largeur; ///< Largeur de la carte, en tiles
        int m_hauteur; ///< Hauteur de la carte, en tiles

        Pos m_ptDeDepart; ///< Le point de départ du joueur sur la carte, en tiles

        int** m_data; ///< Grille contenant les ID des tiles à afficher

        Tileset m_tileset; ///< Le Tileset de la Carte

        std::string m_cheminFichier; ///< Chemin du fichier à charger
};

#endif // CARTE_H
