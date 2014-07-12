#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include <string>

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'�cran
        Joueur(int posX, int posY);

        void gererEvenement(); // R�cup�re un �v�nement et v�rifie si celui-ci modifie le Joueur
        void deplacer(); // D�place le personnage
    protected:
    private:
        int direction; // La direction actuelle
        int dirPrecedente; // La direction de la trame pr�c�dente

        Texture m_sprites[8]; // Les diff�rents sprites du Joueur

        enum {BAS, HAUT, DROITE, GAUCHE, BAS_GAUCHE, HAUT_GAUCHE, HAUT_DROITE, BAS_DROITE, IMMOBILE}; // Les directions que peut avoir le personnage
};

#endif // JOUEUR_H
