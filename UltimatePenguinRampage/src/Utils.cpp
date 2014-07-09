#include <iostream>
#include <SDL.h>

#include "Utils.h"

SDL_Window* Utils::fenetre = NULL;
SDL_Renderer* Utils::renderer = NULL;

bool Utils::initialisation() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur : Impossible d'initialiser la SDL." << std::endl;
        return false;
    } else {
        Utils::fenetre = SDL_CreateWindow( "Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Utils::SCREEN_WIDTH, Utils::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if(Utils::fenetre == NULL) {
            std::cout << "Erreur : Echec de la creation de la fenetre." << std::endl;
            return false;
        } else {
            Utils::renderer = SDL_CreateRenderer(Utils::fenetre, -1, SDL_RENDERER_ACCELERATED);

            if(Utils::renderer == NULL) {
                std::cout << "Erreur : Echec de la creation du renderer." << std::endl;
                return false;
            } else {
                SDL_SetRenderDrawColor(Utils::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
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
