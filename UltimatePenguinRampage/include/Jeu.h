#ifndef JEU_H
#define JEU_H

#include <SDL.h>
#include "Joueur.h"

class Jeu
{
    public:
        Jeu(); // Constructeur
        ~Jeu(); // Destructeur

    protected:
    private:
        int start(); // Lance le jeu

        Joueur* j1; // Personnage
};

#endif // JEU_H
