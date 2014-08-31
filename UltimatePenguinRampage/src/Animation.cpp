#include <iostream>

#include "Animation.h"
#include "Constantes.h"
#include "Utils.h"

Animation::Animation() : m_nombreImages(0), m_imageActuelle(0), m_vitesseAnimation(0), m_direction(DIR_IMMOBILE)
{
    m_plancheSprites.charger("img/PB.bmp");
    m_nombreImages = 5;
    m_vitesseAnimation = 10;
    std::cout << "Animation chargee." << std::endl;
}

Animation::Animation(std::string cheminFichier) : m_nombreImages(0), m_imageActuelle(0), m_vitesseAnimation(0), m_direction(DIR_IMMOBILE)
{
    charger(cheminFichier);
}

Animation::~Animation()
{
    m_plancheSprites.liberer();
}

void Animation::charger(std::string cheminFichier) {

}

void Animation::update() {
    m_imageActuelle++;
    if(m_imageActuelle / m_vitesseAnimation >= m_nombreImages) {
        m_imageActuelle = 0;
    }
}

void Animation::render(int x, int y) {
    SDL_Rect renderQuad = {x, y, LARGEUR_TILE, HAUTEUR_TILE};
    SDL_Rect clipQuad = {(m_imageActuelle/m_vitesseAnimation)*LARGEUR_TILE, 1*HAUTEUR_TILE, LARGEUR_TILE, HAUTEUR_TILE};
    SDL_RenderCopy(Utils::renderer, m_plancheSprites.getImage(), &clipQuad, &renderQuad);
}
