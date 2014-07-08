#ifndef ENNEMI_H
#define ENNEMI_H

#include <iostream>
#include <string>
#include "Personnage.h"



class Ennemi : public Personnage
{
    public:
        void suisJoueur(int posJoueur[2]);
    protected:
    private:

};

#endif // ENNEMI_H
