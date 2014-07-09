#include <iostream>
#include <SDL.h>

#include "Utils.h"

SDL_Window* Utils::fenetre = NULL;
SDL_Surface* Utils::ecran = NULL;

bool Utils::initialisation() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur : Impossible d'initialiser la SDL." << std::endl;
        return false;
    } else {
        Utils::fenetre = SDL_CreateWindow( "Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Utils::SCREEN_WIDTH, Utils::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(Utils::fenetre == NULL) {
            std::cout << "Erreur : Echec de la creation de la fenetre." << std::endl;
        } else {
            Utils::ecran = SDL_GetWindowSurface(Utils::fenetre);
        }
    }

    return true;
}

void Utils::quitter() {
    SDL_DestroyWindow(Utils::fenetre);
    Utils::fenetre = NULL;

    SDL_Quit();
}

SDL_Surface* Utils::loadBMP(std::string chemin, SDL_Surface* &ecran) {
    SDL_Surface* retour = NULL; // La surface à renvoyer

    SDL_Surface* chargee = SDL_LoadBMP(chemin.c_str()); // La surface chargée
    SDL_SetColorKey(chargee, SDL_TRUE, SDL_MapRGB(chargee->format, 255, 0, 255)); //Transparence

    if(chargee == NULL) { // Gestion de l'échec du chargement
        std::cout << "Erreur : L'image " << chemin << " n'a pas pu etre chargee." << std::endl;
        return NULL;
    } else {
        retour = SDL_ConvertSurface(chargee, ecran->format, NULL); // Optimisation de la surface

        if(retour == NULL) { // Gestion de l'échec de l'optimisation
            std::cout << "Erreur : L'image chargee n'a pas pu etre optimisee." << std::endl;
            retour = chargee;
        }

        SDL_FreeSurface(chargee); // Libération de la surface chargée
    }

    return retour;
}
