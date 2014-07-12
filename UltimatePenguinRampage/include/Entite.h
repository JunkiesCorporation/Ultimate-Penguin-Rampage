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

        void render(); // Affiche l'Entite � l'ecran

        virtual void deplacer() = 0; // G�re le d�placement de l'Entite
    protected:
        // Position de l'Entite sur le niveau
        int m_posX;
        int m_posY;

        Direction m_direction; // La direction actuelle de l'Entite
        Direction m_dirPrecedente; // La direction � la trame Precedente

        Texture* m_sprite; // La texture � afficher de l'Entite
    private:
};

#endif // ENTITE_H
