#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture
{
    public:
        Texture(std::string chemin); // Constructeur
        ~Texture(); // Destructeur

        void liberer(); // Libère la texture (pour détruire ou en changer)
        void charger(std::string chemin); // Charge la texture
        void render(int x, int y); // Afficher la texture à la position

        int getLargeur(); // Getter : retourne m_largeur
        int getHauteur(); // Getter : retourne m_hauteur
    protected:
    private:
        SDL_Texture* m_image; // Contient la texture

        int m_largeur; // Largeur de l'image
        int m_hauteur; // Hauteur de l'image
};

#endif // SPRITE_H
