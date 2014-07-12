#include <cmath>
#include <iostream>

#include "Joueur.h"
#include "Utils.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur() : Personnage(), direction(IMMOBILE), dirPrecedente(IMMOBILE)
{
    // Chargement des 8 textures du Joueur
    m_sprites[BAS] = *(new Texture("img/PBface.bmp"));
    m_sprites[BAS_GAUCHE] = *(new Texture("img/PBbasgauche.bmp"));
    m_sprites[GAUCHE] = *(new Texture("img/PBgauche.bmp"));
    m_sprites[HAUT_GAUCHE] = *(new Texture("img/PBhautgauche.bmp"));
    m_sprites[HAUT] = *(new Texture("img/PBdos.bmp"));
    m_sprites[HAUT_DROITE] = *(new Texture("img/PBhautdroite.bmp"));
    m_sprites[DROITE] = *(new Texture("img/PBdroite.bmp"));
    m_sprites[BAS_DROITE] = *(new Texture("img/PBbasdroite.bmp"));

    m_sprite = &m_sprites[BAS]; // Attribution de la première texture

    // Positionnement du Joueur au centre de l'écran
    m_posX = (Utils::SCREEN_WIDTH - m_sprite->getLargeur()) / 2;
    m_posY = (Utils::SCREEN_HEIGHT - m_sprite->getHauteur()) / 2;
}

Joueur::Joueur(int posX, int posY) : Personnage(posX, posY), direction(IMMOBILE), dirPrecedente(IMMOBILE)
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

    if((direction != dirPrecedente) && (direction != IMMOBILE)) { // Change le sprite si nécessaire
        m_sprite = &m_sprites[direction];
    }

    dirPrecedente = direction;

    // Faudrait quand même pas qu'il sorte de l'écran ce pingouin
    if(m_posX < 0) { m_posX = 0; }
    if(m_posX + m_sprite->getLargeur() > Utils::SCREEN_WIDTH) { m_posX = Utils::SCREEN_WIDTH - m_sprite->getLargeur(); }
    if(m_posY < 0) { m_posY = 0; }
    if(m_posY + m_sprite->getHauteur() > Utils::SCREEN_HEIGHT) { m_posY = Utils::SCREEN_HEIGHT - m_sprite->getHauteur(); }

}
