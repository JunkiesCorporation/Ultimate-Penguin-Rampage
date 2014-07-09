#include <cmath>
#include "Joueur.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

enum {BAS, HAUT, DROITE, GAUCHE, BAS_GAUCHE, HAUT_GAUCHE, HAUT_DROITE, BAS_DROITE};

Joueur::Joueur(std::string cheminImage) : Personnage(cheminImage), posPrecedente(BAS)
{
}

Joueur::Joueur(int posX, int posY, std::string cheminImage) : Personnage(posX, posY, cheminImage), posPrecedente(BAS)
{
}

void Joueur::gererEvenement() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    // Chacun des 8 contrôles suivants bougent et change l'image du Joueur en fonction de sa direction
    if(currentKeyStates[SDL_SCANCODE_DOWN] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_posY += VITESSE_JOUEUR;
        if(posPrecedente != BAS) { m_sprite.charger("img/PBface.bmp"); posPrecedente = BAS; }
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_posY -= VITESSE_JOUEUR;
        if(posPrecedente != HAUT) { m_sprite.charger("img/PBdos.bmp"); posPrecedente = HAUT; }
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_posX -= VITESSE_JOUEUR;
        if(posPrecedente != GAUCHE) { m_sprite.charger("img/PBgauche.bmp"); posPrecedente = GAUCHE; }
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_posX += VITESSE_JOUEUR;
        if(posPrecedente != DROITE) { m_sprite.charger("img/PBdroite.bmp"); posPrecedente = DROITE; }
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_posX -= VITESSE_ANGLE; m_posY += VITESSE_ANGLE;
        if(posPrecedente != BAS_GAUCHE) { m_sprite.charger("img/PBbasgauche.bmp"); posPrecedente = BAS_GAUCHE; }
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_posX -= VITESSE_ANGLE; m_posY -= VITESSE_ANGLE;
        if(posPrecedente != HAUT_GAUCHE) { m_sprite.charger("img/PBhautgauche.bmp"); posPrecedente = HAUT_GAUCHE; }
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_posX += VITESSE_ANGLE; m_posY -= VITESSE_ANGLE;
        if(posPrecedente != HAUT_DROITE) { m_sprite.charger("img/PBhautdroite.bmp"); posPrecedente = HAUT_DROITE; }
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_posX += VITESSE_ANGLE; m_posY += VITESSE_ANGLE;
        if(posPrecedente != BAS_DROITE) { m_sprite.charger("img/PBbasdroite.bmp"); posPrecedente = BAS_DROITE; }
    }
}
