#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include <string>

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'écran
        Joueur(int posX, int posY);

        void gererEvenement(); // Récupère un événement et vérifie si celui-ci modifie le Joueur
        void deplacer(); // Déplace le personnage
    protected:
    private:
        int direction; // La direction actuelle
        int dirPrecedente; // La direction de la trame précédente

        Texture m_sprites[8]; // Les différents sprites du Joueur

        enum {BAS, HAUT, DROITE, GAUCHE, BAS_GAUCHE, HAUT_GAUCHE, HAUT_DROITE, BAS_DROITE, IMMOBILE}; // Les directions que peut avoir le personnage
};

#endif // JOUEUR_H
