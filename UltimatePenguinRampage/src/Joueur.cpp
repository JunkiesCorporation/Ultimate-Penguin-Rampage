#include <cmath>
#include <iostream>

#include "Joueur.h"
#include "Utils.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur(std::string cheminImage) : Personnage(cheminImage), direction(IMMOBILE), dirPrecedente(IMMOBILE)
{
    m_posX = (Utils::SCREEN_WIDTH - m_sprite.getLargeur()) / 2;
    m_posY = (Utils::SCREEN_HEIGHT - m_sprite.getHauteur()) / 2;

}

Joueur::Joueur(int posX, int posY, std::string cheminImage) : Personnage(posX, posY, cheminImage), direction(IMMOBILE), dirPrecedente(IMMOBILE)
{
}

void Joueur::gererEvenement() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    // Chacun des 8 contrôles suivants change la direction du Joueur
    if(currentKeyStates[SDL_SCANCODE_DOWN] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        direction = BAS;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        direction = HAUT;
    } else if (currentKeyStates[SDL_SCANCODE_LEFT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        direction = GAUCHE;
    } else if (currentKeyStates[SDL_SCANCODE_RIGHT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        direction = DROITE;
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        direction = BAS_GAUCHE;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        direction = HAUT_GAUCHE;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        direction = HAUT_DROITE;
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
       direction = BAS_DROITE;
    } else {
        direction = IMMOBILE;
    }

}

void Joueur::deplacer() {
    switch(direction) { // Déplace le joueur en fonction de sa direction
        case BAS: m_posY += VITESSE_JOUEUR; break;
        case BAS_GAUCHE: m_posY += VITESSE_ANGLE; m_posX -= VITESSE_ANGLE; break;
        case GAUCHE: m_posX -= VITESSE_JOUEUR; break;
        case HAUT_GAUCHE: m_posY -= VITESSE_ANGLE; m_posX -= VITESSE_ANGLE; break;
        case HAUT: m_posY -= VITESSE_JOUEUR; break;
        case HAUT_DROITE: m_posY -= VITESSE_ANGLE; m_posX += VITESSE_ANGLE; break;
        case DROITE: m_posX += VITESSE_JOUEUR; break;
        case BAS_DROITE: m_posY += VITESSE_ANGLE; m_posX += VITESSE_ANGLE; break;
    }

    if(direction != dirPrecedente) { // Change le sprite si nécessaire
        switch(direction) {
            case BAS: m_sprite.charger("img/PBface.bmp"); break;
            case BAS_GAUCHE: m_sprite.charger("img/PBbasgauche.bmp"); break;
            case GAUCHE: m_sprite.charger("img/PBgauche.bmp"); break;
            case HAUT_GAUCHE: m_sprite.charger("img/PBhautgauche.bmp"); break;
            case HAUT: m_sprite.charger("img/PBdos.bmp"); break;
            case HAUT_DROITE: m_sprite.charger("img/PBhautdroite.bmp"); break;
            case DROITE: m_sprite.charger("img/PBdroite.bmp"); break;
            case BAS_DROITE: m_sprite.charger("img/PBbasdroite.bmp"); break;
        }
    }

    dirPrecedente = direction;

    // Faudrait quand même pas qu'il sorte de l'écran ce pingouin
    if(m_posX < 0) { m_posX = 0; }
    if(m_posX + m_sprite.getLargeur() > Utils::SCREEN_WIDTH) { m_posX = Utils::SCREEN_WIDTH - m_sprite.getLargeur(); }
    if(m_posY < 0) { m_posY = 0; }
    if(m_posY + m_sprite.getHauteur() > Utils::SCREEN_HEIGHT) { m_posY = Utils::SCREEN_HEIGHT - m_sprite.getHauteur(); }

}
