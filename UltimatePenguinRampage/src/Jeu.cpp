#include <stdio.h>

#include "Jeu.h"
#include "Projectile.h"
#include "Utils.h"
#include "Enums.h"

// Construceur
Jeu::Jeu() {
    j1 = new Joueur();
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

    Projectile test(DIR_BAS_DROITE, 4);

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
        j1->gererEvenement();
        j1->deplacer();
        test.deplacer();

        SDL_RenderClear(Utils::renderer);

        j1->render();
        test.render();

        SDL_RenderPresent(Utils::renderer);

    }

    return 0;
}
