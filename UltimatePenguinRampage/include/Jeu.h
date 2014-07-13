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

        static std::vector<Projectile*> projectiles; // Les projectiles en jeu
    protected:
    private:
        int start(); // Lance le jeu
        void update(); // Met à jour tous les éléments
        void render(); // Affiche tous les éléments

        Joueur* m_j1; // Personnage
};

#endif // JEU_H
