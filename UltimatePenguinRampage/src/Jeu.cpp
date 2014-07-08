#include <stdio.h>
#include "Jeu.h"
#include "Utils.h"

// Construceur
Jeu::Jeu(SDL_Window* &fenetre, SDL_Surface* &ecran) {
    moi = new Joueur(Utils::loadBMP("img/PBface.bmp", ecran));
    start(fenetre, ecran);
}

// Destructeur
Jeu::~Jeu() {
}

// Gère tout le jeu
int Jeu::start(SDL_Window* &fenetre, SDL_Surface* &ecran) {
    bool quit(false);
    SDL_Event e;
    SDL_BlitSurface(moi->getSprite(), NULL, ecran, NULL);
    SDL_UpdateWindowSurface(fenetre);
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
