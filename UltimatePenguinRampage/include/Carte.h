#ifndef CARTE_H
#define CARTE_H

#include <string>

#include "Tileset.h"

class Carte
{
    public:
        Carte(std::string); // Constructeur

        ~Carte(); // Destructeur

        void render(); // Affiche la carte

    protected:
    private:
        void charger(); // Lis le fichier associ� � la carte

        int m_largeur; // Largeur de la carte, en tiles
        int m_hauteur; // Hauteur de la carte, en tile

        int** m_data; // Grille contenant les id des cartes � afficher
        Tileset m_tileset;
        std::string m_cheminFichier; // Chemin du fichier � charger
};

#endif // CARTE_H
