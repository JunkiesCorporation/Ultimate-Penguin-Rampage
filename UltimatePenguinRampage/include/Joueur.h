#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        Joueur(SDL_Surface*); // Constructeur

        void gererEvenement(SDL_Event&); // Récupère un événement et vérifie si celui-ci modifie le Joueur

    protected:
    private:
};

#endif // JOUEUR_H
