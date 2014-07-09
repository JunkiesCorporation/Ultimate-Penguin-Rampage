#include <iostream>
#include "Utils.h"

SDL_Surface* Utils::loadBMP(std::string chemin, SDL_Surface* &ecran) {
    SDL_Surface* retour = NULL; // La surface à renvoyer

    SDL_Surface* chargee = SDL_LoadBMP(chemin.c_str()); // La surface chargée
    SDL_SetColorKey(chargee, SDL_TRUE, SDL_MapRGB(chargee->format, 255, 0, 255)); //Transparence

    if(chargee == NULL) { // Gestion de l'échec du chargement
        std::cout << "Erreur : L'image " << chemin << " n'a pas pu être chargée." << std::endl;
        return NULL;
    } else {
        retour = SDL_ConvertSurface(chargee, ecran->format, NULL); // Optimisation de la surface

        if(retour == NULL) { // Gestion de l'échec de l'optimisation
            std::cout << "Erreur : L'image chargée n'a pas pu être optimisée." << std::endl;
            retour = chargee;
        }

        SDL_FreeSurface(chargee); // Libération de la surface chargée
    }

    return retour;
}
