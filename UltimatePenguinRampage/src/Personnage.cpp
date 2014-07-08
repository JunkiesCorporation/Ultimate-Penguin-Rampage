#include "Personnage.h"

using namespace std;

Personnage::Personnage(SDL_Surface* sprite) {
    m_sprite = sprite;
}

Personnage::~Personnage() {
    SDL_FreeSurface(m_sprite);
    delete m_sprite;
}

void Personnage::subitDegats(int nbDegats) {

}
void Personnage::utiliserArme() {

}

SDL_Surface* Personnage::getSprite() {
    return m_sprite;
}
