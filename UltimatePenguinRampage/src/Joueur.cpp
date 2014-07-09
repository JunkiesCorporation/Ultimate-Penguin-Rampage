#include <cmath>
#include "Joueur.h"

const int VITESSE_JOUEUR = 5;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur(std::string cheminImage) : Personnage(cheminImage)
{
}

Joueur::Joueur(int posX, int posY, std::string cheminImage) : Personnage(posX, posY, cheminImage)
{
}

void Joueur::gererEvenement() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_DOWN] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_posY += VITESSE_JOUEUR;
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_posY -= VITESSE_JOUEUR;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_posX -= VITESSE_JOUEUR;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_posX += VITESSE_JOUEUR;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_posX -= VITESSE_ANGLE;
        m_posY += VITESSE_ANGLE;
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_posX -= VITESSE_ANGLE;
        m_posY -= VITESSE_ANGLE;
    }
    if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_posX += VITESSE_ANGLE;
        m_posY -= VITESSE_ANGLE;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_posX += VITESSE_ANGLE;
        m_posY += VITESSE_ANGLE;
    }
}
