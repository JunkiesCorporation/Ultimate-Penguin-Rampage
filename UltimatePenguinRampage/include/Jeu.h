#ifndef JEU_H
#define JEU_H

#include <vector>

#include "Joueur.h"
#include "Projectile.h"

class Jeu
{
    public:
        Jeu(); // Constructeur
        ~Jeu(); // Destructeur

        std::vector<Projectile*> projectiles;
    protected:
    private:
        int start(); // Lance le jeu

        Joueur* j1; // Personnage
};

#endif // JEU_H
