#ifndef ENTITE_H
#define ENTITE_H

#include <vector>

#include "Texture.h"
#include "Enums.h"
#include "Carte.h"
#include "Struct.h"

class Entite
{
    public:
        Entite();
        Entite(int x, int y);
        Entite(int x, int y, Direction direction);

        virtual ~Entite();

        void render(); // Affiche l'Entite � l'ecran
        virtual void update(Carte const& carte) = 0;

    protected:
        Pos m_pos; ///< Position de l'Entite sur le niveau
        Pos m_posPrecedente; ///< Position de l'Entite sur le niveau � la trame pr�c�dente

        Direction m_direction; ///< La direction de l'Entite
        Direction m_dirPrecedente; ///< La direction de l'Entite � la trame pr�c�dente

        Texture* m_sprite; ///< La Texture de l'Entite
    private:
};

#endif // ENTITE_H
