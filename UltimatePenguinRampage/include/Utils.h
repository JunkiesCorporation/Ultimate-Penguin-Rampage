#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <string>

class Utils
{
    public:
         static SDL_Surface* loadBMP(std::string, SDL_Surface*&); // Charge l'image du chemin donné
    protected:
    private:
};

#endif // UTILS_H
