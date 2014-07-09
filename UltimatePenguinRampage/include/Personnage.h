#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SDL.h>

class Personnage
{
    public:
        Personnage(SDL_Surface*); // Constructeur
        ~Personnage(); // Destructeur

        void subitDegats(int nbDegats); // Enlève de la vie au Personnage
        void utiliserArme(); // Enclenche l'utilisation de l'arme
        void gererEvenement(SDL_Event&); // Gère les événements qui concernent le Personnage

        SDL_Surface* getSprite(); // Getter : retourne m_sprite
    protected:
    private:
        int m_pdv;
        int m_mana;
        int m_posX;
        int m_posY;
        bool m_vivant;
        SDL_Surface* m_sprite; // L'image du Personnage
};

#endif // PERSONNAGE_H
