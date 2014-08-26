#ifndef ENNEMI_H
#define ENNEMI_H

#include <iostream>
#include <string>
#include "Personnage.h"
#include "Joueur.h"

class Ennemi : public Personnage
{
    public:
        Ennemi(int x, int y);

        void update(Carte const& carte);
        void update(Carte const& carte, Joueur const& joueur);
    protected:
    private:

};

#endif // ENNEMI_H
