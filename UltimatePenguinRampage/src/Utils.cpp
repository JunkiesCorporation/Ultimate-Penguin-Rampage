#include <iostream>
#include "Utils.h"

SDL_Surface* Utils::loadBMP(std::string chemin, SDL_Surface* &ecran) {
    SDL_Surface* retour = NULL; // La surface � renvoyer

    SDL_Surface* chargee = SDL_LoadBMP(chemin.c_str()); // La surface charg�e
    SDL_SetColorKey(chargee, SDL_TRUE, SDL_MapRGB(chargee->format, 255, 0, 255)); //Transparence

    if(chargee == NULL) { // Gestion de l'�chec du chargement
        std::cout << "Erreur : L'image " << chemin << " n'a pas pu �tre charg�e." << std::endl;
        return NULL;
    } else {
        retour = SDL_ConvertSurface(chargee, ecran->format, NULL); // Optimisation de la surface

        if(retour == NULL) { // Gestion de l'�chec de l'optimisation
            std::cout << "Erreur : L'image charg�e n'a pas pu �tre optimis�e." << std::endl;
            retour = chargee;
        }

        SDL_FreeSurface(chargee); // Lib�ration de la surface charg�e
    }

    return retour;
}
