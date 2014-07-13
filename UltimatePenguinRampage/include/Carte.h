#ifndef CARTE_H
#define CARTE_H

#include <string>

class Carte
{
    public:
        Carte(std::string); // Constructeur
        ~Carte();

    protected:
    private:
        void charger(); // Lis le fichier associ� � la carte

        int m_largeur;
        int m_hauteur;
        int m_nombreTilesets;

        int** m_data; // Grille contenant les id des cartes � afficher
        std::string m_cheminFichier; // Chemin du fichier � charger
};

#endif // CARTE_H
