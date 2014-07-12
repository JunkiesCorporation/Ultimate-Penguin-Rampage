#include <cmath>
#include <iostream>

#include "Joueur.h"
#include "Utils.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur() : Personnage(), m_direction(DIR_IMMOBILE), m_dirPrecedente(DIR_IMMOBILE)
{
    // Chargement des 8 textures du Joueur
    m_sprites[DIR_BAS] = *(new Texture("img/PBface.bmp"));
    m_sprites[DIR_BAS_GAUCHE] = *(new Texture("img/PBbasgauche.bmp"));
    m_sprites[DIR_GAUCHE] = *(new Texture("img/PBgauche.bmp"));
    m_sprites[DIR_HAUT_GAUCHE] = *(new Texture("img/PBhautgauche.bmp"));
    m_sprites[DIR_HAUT] = *(new Texture("img/PBdos.bmp"));
    m_sprites[DIR_HAUT_DROITE] = *(new Texture("img/PBhautdroite.bmp"));
    m_sprites[DIR_DROITE] = *(new Texture("img/PBdroite.bmp"));
    m_sprites[DIR_BAS_DROITE] = *(new Texture("img/PBbasdroite.bmp"));

    m_sprite = &m_sprites[DIR_BAS]; // Attribution de la première texture

    // Positionnement du Joueur au centre de l'écran
    m_posX = (Utils::SCREEN_WIDTH - m_sprite->getLargeur()) / 2;
    m_posY = (Utils::SCREEN_HEIGHT - m_sprite->getHauteur()) / 2;
}

void Joueur::gererEvenement() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    // Chacun des 8 contrôles suivants change la direction du Joueur
    if(currentKeyStates[SDL_SCANCODE_DOWN] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_direction = DIR_BAS;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_direction = DIR_HAUT;
    } else if (currentKeyStates[SDL_SCANCODE_LEFT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_direction = DIR_GAUCHE;
    } else if (currentKeyStates[SDL_SCANCODE_RIGHT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_direction = DIR_DROITE;
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_direction = DIR_BAS_GAUCHE;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_direction = DIR_HAUT_GAUCHE;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_direction = DIR_HAUT_DROITE;
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_direction = DIR_BAS_DROITE;
    } else {
        m_direction = DIR_IMMOBILE;
    }

}

void Joueur::deplacer() {
    switch(m_direction) { // Déplace le joueur en fonction de sa direction
        case DIR_BAS: m_posY += VITESSE_JOUEUR; break;
        case DIR_BAS_GAUCHE: m_posY += VITESSE_ANGLE; m_posX -= VITESSE_ANGLE; break;
        case DIR_GAUCHE: m_posX -= VITESSE_JOUEUR; break;
        case DIR_HAUT_GAUCHE: m_posY -= VITESSE_ANGLE; m_posX -= VITESSE_ANGLE; break;
        case DIR_HAUT: m_posY -= VITESSE_JOUEUR; break;
        case DIR_HAUT_DROITE: m_posY -= VITESSE_ANGLE; m_posX += VITESSE_ANGLE; break;
        case DIR_DROITE: m_posX += VITESSE_JOUEUR; break;
        case DIR_BAS_DROITE: m_posY += VITESSE_ANGLE; m_posX += VITESSE_ANGLE; break;
        case DIR_IMMOBILE: break;
    }

    if((m_direction != m_dirPrecedente) && (m_direction != DIR_IMMOBILE)) { // Change le sprite si nécessaire
        m_sprite = &m_sprites[m_direction];
    }

    m_dirPrecedente = m_direction;

    // Faudrait quand même pas qu'il sorte de l'écran ce pingouin
    if(m_posX < 0) { m_posX = 0; }
    if(m_posX + m_sprite->getLargeur() > Utils::SCREEN_WIDTH) { m_posX = Utils::SCREEN_WIDTH - m_sprite->getLargeur(); }
    if(m_posY < 0) { m_posY = 0; }
    if(m_posY + m_sprite->getHauteur() > Utils::SCREEN_HEIGHT) { m_posY = Utils::SCREEN_HEIGHT - m_sprite->getHauteur(); }

}
