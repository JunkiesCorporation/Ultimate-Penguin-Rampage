#include <iostream>

#include "Entite.h"

Entite::Entite() : m_posX(0), m_posY(0), m_direction(DIR_IMMOBILE), m_dirPrecedente(DIR_IMMOBILE), m_sprite(NULL)
{
}

Entite::Entite(int x, int y) : m_posX(x), m_posY(y), m_direction(DIR_IMMOBILE), m_dirPrecedente(DIR_IMMOBILE), m_sprite(NULL)
{
}

Entite::Entite(int x, int y, Direction direction) : m_posX(x), m_posY(y), m_direction(direction), m_dirPrecedente(DIR_IMMOBILE),
        m_sprite(NULL)
{
}

Entite::~Entite()
{
    std::cout << "Destruction!" << std::endl;
    m_sprite->liberer();
    delete m_sprite;
    m_sprite = NULL;
}

void Entite::render() {
    m_sprite->render(m_posX, m_posY);
}
