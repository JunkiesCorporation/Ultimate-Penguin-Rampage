#ifndef JOUEUR_H
#define JOUEUR_H

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'écran

        void gererEvenement(); // Récupère un événement et vérifie si celui-ci modifie le Joueur

        void deplacer();
    protected:
    private:

        Texture m_sprites[8]; // Les différents sprites du Joueur
};

#endif // JOUEUR_H
