#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Texture.h"
#include "Enums.h"

class Projectile
{
    public:
        Projectile(Direction direction); // Constructeur
        Projectile(Direction direction, int vitesse); // Permet de préciser la vitesse
        ~Projectile(); // Destructeur

        void render(); // Affiche le Projectile à l'écran
        void collision(); // Détecte si le Projectile touche quelque chose
        void deplacer(); // Déplace le Projectile
        bool isDehorsEcran(); // Retourne si le Projectile est sorti de l'écran
    protected:
    private:
        // Position sur l'écran
        int m_posX;
        int m_posY;
        int m_vitesseCard; // Vitesse du Projectile dans les quatre directions cardinales
        int m_vitesseAngle; // Vitesse du Projectile dans les quatre autres directions
        Direction m_direction; // La direction du Projectile
        Direction m_dirPrecedente; // La direction de la trame d'avant

        Texture* m_sprite; // Texture
};

#endif // PROJECTILE_H
