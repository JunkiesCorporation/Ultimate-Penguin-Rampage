#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include <string>

#include "Personnage.h"
#include "Enums.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'�cran

        void gererEvenement(); // R�cup�re un �v�nement et v�rifie si celui-ci modifie le Joueur
        void deplacer(); // D�place le personnage
    protected:
    private:
        Direction m_direction; // La direction actuelle
        Direction m_dirPrecedente; // La direction de la trame pr�c�dente

        Texture m_sprites[8]; // Les diff�rents sprites du Joueur
};

#endif // JOUEUR_H
