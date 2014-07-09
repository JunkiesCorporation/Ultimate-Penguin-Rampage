#include "Joueur.h"

int vitesse = 5;
// Constructeur
Joueur::Joueur(std::string cheminImage) : Personnage(cheminImage), m_vitesse(5)
{
}

void Joueur::gererEvenement(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_DOWN:
            this->m_posY += m_vitesse;
            break;
        case SDLK_UP:
            this->m_posY -= m_vitesse;
            break;
        case SDLK_LEFT:
            this->m_posX -= m_vitesse;
            break;
        case SDLK_RIGHT:
            this->m_posX += m_vitesse;
            break;
        }
    }
}
