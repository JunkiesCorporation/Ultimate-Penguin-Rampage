#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

#include "Personnage.h"
#include "Projectile.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'�cran

        void gererEvenement(SDL_Event &e); // R�cup�re un �v�nement et v�rifie si celui-ci modifie le Joueur
        void update();
        void utiliserArme();
    protected:
    private:
        void deplacer(); // D�place le personnage en fonction de sa direction

        int m_reload;
        bool m_toucheDir[8];
        bool m_feu;
        Texture m_sprites[8]; // Les diff�rents sprites du Joueur
};

#endif // JOUEUR_H
