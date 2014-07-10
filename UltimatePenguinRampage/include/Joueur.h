#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL.h>
#include <string>

#include "Personnage.h"

class Joueur : public Personnage
{
    public:
        // Constructeurs
        Joueur(std::string cheminImage); // Initalise la position au centre de l'écran
        Joueur(int posX, int posY, std::string cheminImage);

        void gererEvenement(); // Récupère un événement et vérifie si celui-ci modifie le Joueur
        void deplacer(); // Déplace le personnage
    protected:
    private:
        int direction; // La direction actuelle
        int dirPrecedente; // La direction de la trame précédente
};

#endif // JOUEUR_H
