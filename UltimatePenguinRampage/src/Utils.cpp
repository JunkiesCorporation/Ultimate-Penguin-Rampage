#include <iostream>
#include "Utils.h"

SDL_Surface* Utils::loadBMP(std::string path, SDL_Surface* &ecran) {
    SDL_Surface* retour = NULL;
    SDL_Surface* chargee = SDL_LoadBMP(path.c_str());
    SDL_SetColorKey(chargee, SDL_TRUE, SDL_MapRGB(chargee->format, 255, 0, 255)); //Transparence
    if(chargee == NULL) {
        std::cout << "Erreur : L'image " << path << " n'a pas pu être chargée." << std::endl;
        return NULL;
    } else {
        retour = SDL_ConvertSurface(chargee, ecran->format, NULL);
        if(retour == NULL) {
            std::cout << "Erreur : L'image chargée n'a pas pu être optimisée." << std::endl;
            retour = chargee;
        }
        SDL_FreeSurface(chargee);
    }

    return retour;
}
