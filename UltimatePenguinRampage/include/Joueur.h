#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

#include "Personnage.h"
#include "Projectile.h"
#include "Struct.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'écran

        void gererEvenement(SDL_Event &e); // Récupère un événement et vérifie si celui-ci modifie le Joueur
        void update(Carte const& carte);
        void utiliserArme();
    protected:
    private:
        void deplacer(Carte const& carte); // Déplace le personnage en fonction de sa direction

        int m_reload;
        bool m_toucheDir[8];
        bool m_feu;
        Texture m_sprites[8]; // Les différents sprites du Joueur
};

#endif // JOUEUR_H
