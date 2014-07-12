#include <stdio.h>

#include "Personnage.h"
#include "Utils.h"

Personnage::Personnage() : m_posX(0), m_posY(0), m_sprite(NULL)
{
}

Personnage::Personnage(int posX, int posY) : m_posX(posX), m_posY(posY), m_sprite(NULL)
{
}

Personnage::~Personnage() {
    m_sprite->liberer();
    delete m_sprite;
}

void Personnage::subitDegats(int nbDegats) {

}
void Personnage::utiliserArme() {

}
void Personnage::render() {
    m_sprite->render(m_posX, m_posY);
}

Texture* Personnage::getSprite() {
    return m_sprite;
}
