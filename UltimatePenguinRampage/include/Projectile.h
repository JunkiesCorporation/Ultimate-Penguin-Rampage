#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entite.h"

class Projectile : public Entite
{
    public:
        Projectile();
        Projectile(int x, int y, Direction direction, int vitesseCard);

        ~Projectile();

        void update(Carte const& carte);

        bool isHorsEcran(); // Retourne si le Projectile est sorti de l'écran

    protected:
    private:
        void deplacer(); // Déplace le Projectile

        int m_vitesseCard; // Vitesse du Projectile dans les quatre directions cardinales
        int m_vitesseAngle; // Vitesse du Projectile dans les quatre autres directions
};

#endif // PROJECTILE_H
