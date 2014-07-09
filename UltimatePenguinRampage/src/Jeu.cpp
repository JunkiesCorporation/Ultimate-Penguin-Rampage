#include <stdio.h>
#include "Jeu.h"
#include "Utils.h"

// Construceur
Jeu::Jeu() {
    moi = new Joueur(Utils::loadBMP("img/PBface.bmp", Utils::ecran));
    start();
}

// Destructeur
Jeu::~Jeu() {
}

// Gère tout le jeu
int Jeu::start() {
    printf("Jeu lance.\n");
    bool quit(false);
    SDL_Event e;
    SDL_Texture* penguin = Utils::loadTexture("img/PBface.bmp");
    SDL_RenderClear(Utils::renderer);
    SDL_RenderCopy(Utils::renderer,penguin, NULL, NULL);
    SDL_RenderPresent(Utils::renderer);
    while(!quit) {
        // Gestion des événements
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    printf("Jeu quitte.\n");
                    break;
                }
            }
        }


    }

    return 0;
}
