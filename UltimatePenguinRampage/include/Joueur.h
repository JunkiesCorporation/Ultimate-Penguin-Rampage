#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        Joueur(SDL_Surface*);
        void gererEvenement(SDL_Event&);
    protected:
    private:
};

#endif // JOUEUR_H
