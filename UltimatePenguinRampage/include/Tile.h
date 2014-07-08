#ifndef TILE_H
#define TILE_H

#include <SDL.h>


class Tile
{
    public:
        Tile();

    protected:
    private:
        char m_symbole;
        bool m_solide; //si le sprite est infranchissable m_solide=true, sinon false
        SDL_Surface m_sprite;

};

#endif // TILE_H
