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
        Joueur(); // Initalise la position au centre de l'écran

        void gererEvenement(); // Récupère un événement et vérifie si celui-ci modifie le Joueur
        void deplacer(); // Déplace le personnage
    protected:
    private:
        Direction m_direction; // La direction actuelle
        Direction m_dirPrecedente; // La direction de la trame précédente

        Texture m_sprites[8]; // Les différents sprites du Joueur
};

#endif // JOUEUR_H
