#include <cmath>
#include <iostream>

#include "Projectile.h"
#include "Utils.h"

Projectile::Projectile(Direction direction): m_posX(0), m_posY(0), m_vitesseCard(0), m_vitesseAngle(0), m_direction(direction),
        m_dirPrecedente(direction), m_sprite(NULL)
{
    m_sprite = new Texture("img/boule_de_neige.bmp");
}

Projectile::Projectile(Direction direction, int vitesse): m_posX(0), m_posY(0), m_vitesseCard(vitesse), m_vitesseAngle(0),
        m_direction(direction), m_dirPrecedente(direction), m_sprite(NULL)
{
    m_vitesseAngle = vitesse * cos(M_PI_4);
    m_sprite = new Texture("img/boule_de_neige.bmp");
}

Projectile::~Projectile()
{
    m_sprite->liberer();
    delete m_sprite;
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

void Projectile::render() {
    m_sprite->render(m_posX, m_posY);
}

bool Projectile::isDehorsEcran() {
    if(m_posX < 0 || m_posY < 0 || m_posX + m_sprite->getLargeur() > Utils::SCREEN_WIDTH || m_sprite->getHauteur() > Utils::SCREEN_HEIGHT) {
        return true;
    }
    return false;
}
