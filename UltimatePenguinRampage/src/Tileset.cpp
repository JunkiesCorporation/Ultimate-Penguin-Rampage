#include <iostream>

#include "Tileset.h"
#include "Utils.h"

Tileset::Tileset() : m_largeur(0), m_hauteur(0), m_largeurTiles(0), m_hauteurTiles(0)
{
    std::cout << "Tileset construit (sans param)" << std::endl;
}

Tileset::Tileset(int largeur, int hauteur, int largeurTiles, int hauteurTiles, std::string chemin) :
    m_largeur(largeur), m_hauteur(hauteur), m_largeurTiles(largeurTiles), m_hauteurTiles(hauteurTiles), m_image(chemin)
{
    std::cout << "Tileset construit (avec param)" << std::endl;
}

Tileset::~Tileset()
{
    std::cout << "Tileset detruit" << std::endl;
    m_image.liberer();
}

void Tileset::render(int tileID, int x, int y) {
    SDL_Rect clipQuad = {((tileID%m_largeur)-1)*m_largeurTiles, (tileID/m_hauteur)*m_hauteurTiles, m_largeurTiles, m_hauteurTiles};
    SDL_Rect renderQuad = {x*m_largeurTiles, y*m_hauteurTiles, m_largeurTiles, m_hauteurTiles};
    SDL_RenderCopy(Utils::renderer, m_image.getImage(), &clipQuad, &renderQuad);
}
