#ifndef JOUEUR_H
#define JOUEUR_H

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'�cran

        void gererEvenement(); // R�cup�re un �v�nement et v�rifie si celui-ci modifie le Joueur

        void deplacer();
    protected:
    private:

        Texture m_sprites[8]; // Les diff�rents sprites du Joueur
};

#endif // JOUEUR_H
