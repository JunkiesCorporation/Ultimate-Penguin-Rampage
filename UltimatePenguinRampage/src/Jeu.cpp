#include <stdio.h>
#include "Jeu.h"
#include "Utils.h"

// Construceur
Jeu::Jeu() {
    moi = new Joueur("img/PBface.bmp");
    start();
}

// Destructeur
Jeu::~Jeu() {
}

// G�re tout le jeu
int Jeu::start() {
    printf("Jeu lance.\n");
    bool quit(false);
    SDL_Event e;

    while(!quit) {
        // Gestion des �v�nements
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    printf("Jeu quitte.\n");
                    break;
                }
            }

            moi->gererEvenement(e);
        }

        SDL_RenderClear(Utils::renderer);

        moi->render();

        SDL_RenderPresent(Utils::renderer);

    }

    return 0;
}
