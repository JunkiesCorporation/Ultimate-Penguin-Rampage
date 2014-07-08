#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SDL.h>

class Personnage
{
    public:
        Personnage(SDL_Surface*);
        ~Personnage();
        void subitDegats(int nbDegats);
        void utiliserArme();
        void gererEvenement(SDL_Event&);

        SDL_Surface* getSprite();
    protected:
    private:
        int m_pdv;
        int m_mana;
        int m_posX;
        int m_posY;
        bool m_vivant;
        SDL_Surface* m_sprite;
};

#endif // PERSONNAGE_H
