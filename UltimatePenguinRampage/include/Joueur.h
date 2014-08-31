#ifndef JOUEUR_H
#define JOUEUR_H

#include "Animation.h"
#include "Personnage.h"
#include "Projectile.h"
#include "Struct.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(Pos ptDeDepart); // Initalise la position au centre de l'�cran

        void gererEvenement(SDL_Event &e); // R�cup�re un �v�nement et v�rifie si celui-ci modifie le Joueur
        void update(Carte const& carte);
        void utiliserArme();
    protected:
    private:
        void deplacer(Carte const& carte); // D�place le personnage en fonction de sa direction

        int m_reload;
        bool m_toucheDir[8];
        bool m_feu;
};

#endif // JOUEUR_H
