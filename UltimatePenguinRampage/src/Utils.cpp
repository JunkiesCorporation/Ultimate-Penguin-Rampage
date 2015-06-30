#include <iostream>
#include <SDL.h>

#include "Utils.h"
#include "Constantes.h"

SDL_Window* Utils::fenetre = NULL;
SDL_Renderer* Utils::renderer = NULL;
SDL_Surface* Utils::screenSurface = NULL;

bool Utils::initialisation() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur : Impossible d'initialiser la SDL." << std::endl;
        return false;
    } else {
        Utils::fenetre = SDL_CreateWindow( "Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_WINDOW_SHOWN );

        if(Utils::fenetre == NULL) {
            std::cout << "Erreur : Echec de la creation de la fenetre." << std::endl;
            return false;
        } else {
            Utils::renderer = SDL_CreateRenderer(Utils::fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if(Utils::renderer == NULL) {
                std::cout << "Erreur : Echec de la creation du renderer." << std::endl;
                return false;
            } else {
                SDL_SetRenderDrawColor(Utils::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
			
			Utils::screenSurface == SDL_GetWindowSurface(Utils::fenetre);
        }
    }

    return true;
}

void Utils::quitter() {
    SDL_DestroyRenderer(Utils::renderer);
    Utils::renderer = NULL;
    SDL_DestroyWindow(Utils::fenetre);
    Utils::fenetre = NULL;

    SDL_Quit();
}
