#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>

class Utils
{
    public:
        static SDL_Surface* loadBMP(std::string, SDL_Surface*&); // Charge l'image du chemin donné
        static bool initialisation(); // Initialisation du programme et de la SDL.
        static void quitter();

        static SDL_Window* fenetre; // La fenêtre du programme
        static SDL_Surface* ecran; // Le contenu de la fenêtre

        static const int SCREEN_WIDTH = 640; // Largeur de l'écran
        static const int SCREEN_HEIGHT = 480; // Hauteur de l'écran

        static int plop;
    protected:
    private:
};

#endif // UTILS_H
