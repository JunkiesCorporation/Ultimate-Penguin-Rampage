#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>

class Utils
{
    public:
        static SDL_Surface* loadBMP(std::string, SDL_Surface*&); // Charge l'image du chemin donn�
        static bool initialisation(); // Initialisation du programme et de la SDL.
        static void quitter();

        static SDL_Window* fenetre; // La fen�tre du programme
        static SDL_Surface* ecran; // Le contenu de la fen�tre

        static const int SCREEN_WIDTH = 640; // Largeur de l'�cran
        static const int SCREEN_HEIGHT = 480; // Hauteur de l'�cran

        static int plop;
    protected:
    private:
};

#endif // UTILS_H
