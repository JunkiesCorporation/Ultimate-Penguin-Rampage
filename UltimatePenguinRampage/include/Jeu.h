#ifndef JEU_H
#define JEU_H

#include <SDL.h>
#include "Joueur.h"

class Jeu
{
    public:
        Jeu(SDL_Window*&, SDL_Surface*&); // Constructeur
        ~Jeu(); // Destructeur

    protected:
    private:
        int start(SDL_Window*&,SDL_Surface*&); // Lance le jeu

        Joueur* moi; // Personnage
};

#endif // JEU_H
