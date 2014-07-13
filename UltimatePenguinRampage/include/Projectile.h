#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entite.h"
#include "Texture.h"
#include "Enums.h"

class Projectile : public Entite
{
    public:
        Projectile();
        Projectile(int x, int y, Direction direction, int vitesseCard);

        void deplacer(); // Déplace le Projectile

        bool isHorsEcran(); // Retourne si le Projectile est sorti de l'écran

    protected:
    private:
        int m_vitesseCard; // Vitesse du Projectile dans les quatre directions cardinales
        int m_vitesseAngle; // Vitesse du Projectile dans les quatre autres directions
};

#endif // PROJECTILE_H
