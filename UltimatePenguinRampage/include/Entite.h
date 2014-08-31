#ifndef ENTITE_H
#define ENTITE_H

#include "Animation.h"
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

        void render(SDL_Rect camera); ///< Affiche l'Entite � l'ecran, par rapport � la position de la cam�ra
        virtual void update(Carte const& carte) = 0;

        Pos getPos() const; ///< Retourne la position de l'Entite
        int getLargeur() const; ///< Retourne la largeur de la texture de l'Entite
        int getHauteur() const; ///< Retourne la hauteur de la texture de l'Entite

    protected:
        Animation m_animation; ///< L'Animation de l'Entite. Remplacera m_sprite.

        Pos m_pos; ///< Position de l'Entite sur le niveau
        Pos m_posPrecedente; ///< Position de l'Entite sur le niveau � la trame pr�c�dente

        Direction m_direction; ///< La direction de l'Entite
        Direction m_dirPrecedente; ///< La direction de l'Entite � la trame pr�c�dente

        Texture* m_sprite; ///< La Texture de l'Entite
    private:
};

#endif // ENTITE_H
