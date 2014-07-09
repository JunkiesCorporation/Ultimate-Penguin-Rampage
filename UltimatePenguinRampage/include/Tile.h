#ifndef TILE_H
#define TILE_H

#include <string>
#include <SDL.h>


class Tile
{
    public:
        Tile(); // Constructeur

    protected:
    private:
        char m_symbole; // ?
        std::string m_nomImage;
        bool m_solide; // Si la case est franchissable ou non
        SDL_Surface m_sprite; // Image de la case

};

#endif // TILE_H
