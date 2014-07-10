#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include <string>

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(std::string cheminImage); // Initalise la position au centre de l'�cran
        Joueur(int posX, int posY, std::string cheminImage);

        void gererEvenement(); // R�cup�re un �v�nement et v�rifie si celui-ci modifie le Joueur
        void deplacer(); // D�place le personnage
    protected:
    private:
        int direction; // La direction actuelle
        int dirPrecedente; // La direction de la trame pr�c�dente
};

#endif // JOUEUR_H
