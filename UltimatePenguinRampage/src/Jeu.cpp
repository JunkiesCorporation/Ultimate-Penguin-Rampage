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
    bool quit(false);
    SDL_Event e;
    SDL_BlitSurface(moi->getSprite(), NULL, Utils::ecran, NULL);
    SDL_UpdateWindowSurface(Utils::fenetre);
    while(!quit) {
        // Gestion des événements
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    break;
                }
            }
            moi->gererEvenement(e);
        }


    }

    return 0;
}
