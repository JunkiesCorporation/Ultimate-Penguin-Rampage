#ifndef JEU_H
#define JEU_H

#include <vector>

#include "Joueur.h"
#include "Projectile.h"
#include "Carte.h"

class Jeu
{
    public:
        Jeu(); // Constructeur
        ~Jeu(); // Destructeur

        static std::vector<Projectile*> projectiles; // Les projectiles en jeu
    protected:
    private:
        int start(); // Lance le jeu
        void update(); // Met � jour tous les �l�ments
        void render(); // Affiche tous les �l�ments

        Joueur* m_j1; // Personnage
        Carte* m_carte; // La carte

};

#endif // JEU_H
