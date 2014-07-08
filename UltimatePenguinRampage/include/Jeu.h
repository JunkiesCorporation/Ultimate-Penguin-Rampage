#ifndef JEU_H
#define JEU_H

#include <SDL.h>
#include "Joueur.h"

class Jeu
{
    public:
        Jeu(SDL_Window*&, SDL_Surface*&); // Constructeur
        ~Jeu();

    protected:
    private:
        int start(SDL_Window*&,SDL_Surface*&); // Lancement du jeu
        Joueur* moi;
};

#endif // JEU_H
