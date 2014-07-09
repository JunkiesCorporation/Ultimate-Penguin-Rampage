#include "Personnage.h"

using namespace std;

// Constructeur
Personnage::Personnage(SDL_Surface* sprite) {
    m_sprite = sprite; // Charge l'image avec le paramètre donné
}

// Destructeur
Personnage::~Personnage() {
    SDL_FreeSurface(m_sprite); // Libère l'image
    delete m_sprite; // Détruit le pointeur
}

void Personnage::subitDegats(int nbDegats) {

}
void Personnage::utiliserArme() {

}

SDL_Surface* Personnage::getSprite() {
    return m_sprite;
}
