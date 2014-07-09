#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include <string>

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        Joueur(std::string cheminImage); // Constructeur
        Joueur(int posX, int posY, std::string cheminImage);

        void gererEvenement(); // Récupère un événement et vérifie si celui-ci modifie le Joueur

    protected:
    private:
        const int m_vitesse;
};

#endif // JOUEUR_H
