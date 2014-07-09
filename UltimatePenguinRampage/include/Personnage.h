#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SDL.h>
#include <string>

#include "Texture.h"

class Personnage
{
    public:
        Personnage(std::string cheminImage); // Constructeur
        Personnage(int posX, int posY, std::string cheminImage);
        ~Personnage(); // Destructeur

        void subitDegats(int nbDegats); // Enl�ve de la vie au Personnage
        void utiliserArme(); // Enclenche l'utilisation de l'arme
        void gererEvenement(); // G�re les �v�nements qui concernent le Personnage
        void render(); // Afficher le Personnage

        Texture getSprite(); // Getter : retourne m_sprite
    protected:
        int m_posX;
        int m_posY;
        int m_pdv;
        int m_mana;
        bool m_vivant;
        Texture m_sprite; // L'image du Personnage
    private:

};

#endif // PERSONNAGE_H
