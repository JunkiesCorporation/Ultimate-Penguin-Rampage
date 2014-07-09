#include "Personnage.h"

using namespace std;

// Constructeur
Personnage::Personnage(SDL_Surface* sprite) {
    m_sprite = sprite; // Charge l'image avec le param�tre donn�
}

// Destructeur
Personnage::~Personnage() {
    SDL_FreeSurface(m_sprite); // Lib�re l'image
    delete m_sprite; // D�truit le pointeur
}

void Personnage::subitDegats(int nbDegats) {

}
void Personnage::utiliserArme() {

}

SDL_Surface* Personnage::getSprite() {
    return m_sprite;
}
