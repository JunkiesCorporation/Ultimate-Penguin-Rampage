#include <cmath>
#include "Joueur.h"

const int VITESSE_JOUEUR = 4;

Joueur::Joueur(std::string cheminImage) : Personnage(cheminImage), m_vitesse(VITESSE_JOUEUR)
{
}

Joueur::Joueur(int posX, int posY, std::string cheminImage) : Personnage(posX, posY, cheminImage), m_vitesse(VITESSE_JOUEUR)
{
}

void Joueur::gererEvenement() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_DOWN] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_posY += m_vitesse;
    } else if (currentKeyStates[SDL_SCANCODE_UP] && !(currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_LEFT])) {
        m_posY -= m_vitesse;
    } else if (currentKeyStates[SDL_SCANCODE_LEFT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_posX -= m_vitesse;
    } else if (currentKeyStates[SDL_SCANCODE_RIGHT] && !(currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN])) {
        m_posX += m_vitesse;
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_posX -= m_vitesse * cos(M_PI_4);
        m_posY += m_vitesse * sin(M_PI_4);
    } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
        m_posX -= m_vitesse * cos(M_PI_4);
        m_posY -= m_vitesse * sin(M_PI_4);
    } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_posX += m_vitesse * cos(M_PI_4);
        m_posY -= m_vitesse * sin(M_PI_4);
    } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
        m_posX += m_vitesse * cos(M_PI_4);
        m_posY += m_vitesse * sin(M_PI_4);
    }
}
