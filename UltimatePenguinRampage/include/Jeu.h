#ifndef JEU_H
#define JEU_H

#include <SDL.h>

class Jeu
{
    public:
        Jeu(SDL_Window*&, SDL_Surface*&); // Constructeur
        ~Jeu();

    protected:
    private:
        int Start(SDL_Window*&,SDL_Surface*&); // Lancement du jeu
};

#endif // JEU_H
