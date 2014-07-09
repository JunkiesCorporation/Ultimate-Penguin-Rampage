#include <stdio.h>

#include "Personnage.h"
#include "Utils.h"

// Constructeur
Personnage::Personnage(std::string cheminImage) : m_posX(0), m_posY(0), m_sprite(cheminImage)
{
}

// Destructeur
Personnage::~Personnage() {
    m_sprite.liberer();
}

void Personnage::subitDegats(int nbDegats) {

}
void Personnage::utiliserArme() {

}
void Personnage::render() {
    m_sprite.render(m_posX, m_posY);
}

Texture Personnage::getSprite() {
    return m_sprite;
}
