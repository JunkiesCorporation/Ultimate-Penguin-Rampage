#ifndef TILE_H
#define TILE_H

#include <string>
#include <SDL.h>

#include "Texture.h"

class Tile
{
    public:
        Tile(); // Constructeur

        bool isSolide(); // Retourne m_solide
        int getId(); // Getter : retourne m_id;
    protected:
    private:
        int m_id;

        bool m_solide; // Si la case est franchissable ou non
        Texture m_texture;
};

#endif // TILE_H
