#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>

class Utils
{
    public:
        static SDL_Texture* loadTexture(std::string); // Charge une texture à partir de l'image du chemin donné
        static bool initialisation(); // Initialisation du programme et de la SDL.
        static void quitter();

        static SDL_Window* fenetre; // La fenêtre du programme
        static SDL_Renderer* renderer; // Permet d'afficher du contenu dans la fenêtre

        static const int SCREEN_WIDTH = 640; // Largeur de l'écran
        static const int SCREEN_HEIGHT = 480; // Hauteur de l'écran
    protected:
    private:
};

#endif // UTILS_H
