#ifndef JEU_H
#define JEU_H

#include <vector>

#include "Joueur.h"
#include "Ennemi.h"
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
        void update(); // Met à jour tous les éléments
        void render(); // Affiche tous les éléments

        Joueur* m_j1; ///< Personnage
        Ennemi* m_ennemi1;
        Carte* m_carte; ///< La carte
        SDL_Rect m_camera; ///< La camera du jeu

};

#endif // JEU_H
