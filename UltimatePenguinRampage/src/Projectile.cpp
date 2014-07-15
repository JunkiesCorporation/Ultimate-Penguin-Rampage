#include <cmath>
#include <iostream>

#include "Projectile.h"
#include "Utils.h"

static int nombre(0);

Projectile::Projectile(): Entite()
{
    m_sprite = new Texture("img/boule_de_neige.bmp");
}

Projectile::Projectile(int x, int y, Direction direction, int vitesseCard): Entite(x, y, direction), m_vitesseCard(vitesseCard)
{
    if(direction == DIR_IMMOBILE) {m_direction = DIR_BAS; }
    m_vitesseAngle = vitesseCard * cos(M_PI_4);
    m_sprite = new Texture("img/boule_de_neige.bmp");

    nombre++;
    std::cout << nombre << std::endl;
}

Projectile::~Projectile(){
    nombre--;
    std::cout << nombre << " - ";
}

void Projectile::update() {
    deplacer();
}

void Projectile::deplacer() {
    switch(m_direction) {
        case DIR_BAS: m_posY += m_vitesseCard; break;
        case DIR_BAS_GAUCHE: m_posY += m_vitesseAngle; m_posX -= m_vitesseAngle; break;
        case DIR_GAUCHE: m_posX -= m_vitesseCard; break;
        case DIR_HAUT_GAUCHE: m_posY -= m_vitesseAngle; m_posX -= m_vitesseAngle; break;
        case DIR_HAUT: m_posY -= m_vitesseCard; break;
        case DIR_HAUT_DROITE: m_posY -= m_vitesseAngle; m_posX += m_vitesseAngle; break;
        case DIR_DROITE: m_posX += m_vitesseCard; break;
        case DIR_BAS_DROITE: m_posY += m_vitesseAngle; m_posX += m_vitesseAngle; break;
        case DIR_IMMOBILE: break;
    }
}

bool Projectile::isHorsEcran() {
    if(m_posX + m_sprite->getLargeur() < 0 || m_posY + m_sprite->getHauteur() < 0 || m_posX > Utils::SCREEN_WIDTH || m_posY > Utils::SCREEN_HEIGHT) {
        return true;
    }
    return false;
}
