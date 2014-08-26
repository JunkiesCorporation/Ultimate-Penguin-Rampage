#include "Ennemi.h"
#include "Enums.h"
#include "Images.h"
#include <math.h>

const int VITESSE_ENNEMI(2);
const int VITESSE_ENNEMI_ANGLE = VITESSE_ENNEMI * cos(M_PI_4);

Ennemi::Ennemi(int x, int y) : Personnage(x, y) {
    m_sprite = &Images::spritesEnnemi[DIR_BAS];
    m_direction = DIR_BAS;
}

void Ennemi::update(Carte const& carte, Joueur const& joueur) {
    double xOffset = joueur.getPos().x - m_pos.x;
    double yOffset = joueur.getPos().y - m_pos.y;
    double hypotenuse = sqrt(xOffset*xOffset + yOffset*yOffset);
    double angle(0);

    if(hypotenuse != 0) {
        angle = acos(xOffset / hypotenuse);
    }
    if(yOffset < 0) {angle *= -1;}

    double M_PI_8 = M_PI_4 / 2;

    if(angle < M_PI_8 && angle > - M_PI_8) {m_direction = DIR_DROITE;}
    if(angle > M_PI_8 && angle < 3 * M_PI_8) {m_direction = DIR_BAS_DROITE;}
    if(angle > 3 * M_PI_8 && angle < 5 * M_PI_8) {m_direction = DIR_BAS;}
    if(angle > 5 * M_PI_8 && angle < 7 * M_PI_8) {m_direction = DIR_BAS_GAUCHE;}
    if(angle > 7 * M_PI_8 || angle < -7 * M_PI_8) {m_direction = DIR_GAUCHE;}
    if(angle > -7 * M_PI_8 && angle < -5 * M_PI_8) {m_direction = DIR_HAUT_GAUCHE;}
    if(angle > -5 * M_PI_8 && angle < -3 * M_PI_8) {m_direction = DIR_HAUT;}
    if(angle > -3 * M_PI_8 && angle < -M_PI_8) {m_direction = DIR_HAUT_DROITE;}

    switch(m_direction) { // Déplace le joueur en fonction de sa direction
        case DIR_BAS: m_pos.y += VITESSE_ENNEMI; break;
        case DIR_BAS_GAUCHE: m_pos.y += VITESSE_ENNEMI_ANGLE; m_pos.x -= VITESSE_ENNEMI_ANGLE; break;
        case DIR_GAUCHE: m_pos.x -= VITESSE_ENNEMI; break;
        case DIR_HAUT_GAUCHE: m_pos.y -= VITESSE_ENNEMI_ANGLE; m_pos.x -= VITESSE_ENNEMI_ANGLE; break;
        case DIR_HAUT: m_pos.y -= VITESSE_ENNEMI; break;
        case DIR_HAUT_DROITE: m_pos.y -= VITESSE_ENNEMI_ANGLE; m_pos.x += VITESSE_ENNEMI_ANGLE; break;
        case DIR_DROITE: m_pos.x += VITESSE_ENNEMI; break;
        case DIR_BAS_DROITE: m_pos.y += VITESSE_ENNEMI_ANGLE; m_pos.x += VITESSE_ENNEMI_ANGLE; break;
        case DIR_IMMOBILE: break;
    }

}

void Ennemi::update(Carte const& carte) {
}
