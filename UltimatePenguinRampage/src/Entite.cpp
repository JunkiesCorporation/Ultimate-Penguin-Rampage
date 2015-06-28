#include <iostream>

#include "Entite.h"

Entite::Entite() : m_direction(DIR_IMMOBILE), m_dirPrecedente(DIR_IMMOBILE), m_sprite(NULL)
{
    m_pos.x = 0;
    m_pos.y = 0;
    m_posPrecedente = m_pos;
}

Entite::Entite(int x, int y) : m_direction(DIR_IMMOBILE), m_dirPrecedente(DIR_IMMOBILE), m_sprite(NULL)
{
    m_pos.x = x;
    m_pos.y = y;
    m_posPrecedente = m_pos;
}

Entite::Entite(int x, int y, Direction direction) : m_direction(direction), m_dirPrecedente(DIR_IMMOBILE),
        m_sprite(NULL)
{
    m_pos.x = x;
    m_pos.y = y;
    m_posPrecedente = m_pos;
}

Entite::~Entite()
{
    std::cout << "Entite detruite" << std::endl;
    m_sprite->liberer();
    delete m_sprite;
    m_sprite = NULL;
}

void Entite::render(SDL_Rect camera) {
    m_sprite->render(m_pos.x - camera.x, m_pos.y - camera.y);
    //m_animation.render(m_pos.x - camera.x, m_pos.y - camera.y);
}

Pos Entite::getPos() const {
    return m_pos;
}
int Entite::getLargeur() const {
    return m_sprite->getLargeur();
}
int Entite::getHauteur() const {
    return m_sprite->getHauteur();
}
