#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

#include "Personnage.h"
#include "Projectile.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(); // Initalise la position au centre de l'écran

        void gererEvenement(SDL_Event &e); // Récupère un événement et vérifie si celui-ci modifie le Joueur
        void deplacer();
        void update(std::vector<Projectile*> &projectiles);
        void tirer(std::vector<Projectile*> &projectiles);
    protected:
    private:
        int reload;
        int vitX;
        int vitY;
        bool toucheDir[8];
        bool feu;
        Texture m_sprites[8]; // Les différents sprites du Joueur
};

#endif // JOUEUR_H
