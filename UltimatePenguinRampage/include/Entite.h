#ifndef ENTITE_H
#define ENTITE_H

#include "Texture.h"
#include "Enums.h"

class Entite
{
    public:
        Entite();
        Entite(int x, int y);
        Entite(int x, int y, Direction direction);

        virtual ~Entite();

        void render(); // Affiche l'Entite à l'ecran

        virtual void deplacer() = 0; // Gère le déplacement de l'Entite
    protected:
        // Position de l'Entite sur le niveau
        int m_posX;
        int m_posY;

        Direction m_direction; // La direction actuelle de l'Entite
        Direction m_dirPrecedente; // La direction à la trame Precedente

        Texture* m_sprite; // La texture à afficher de l'Entite
    private:
};

#endif // ENTITE_H
