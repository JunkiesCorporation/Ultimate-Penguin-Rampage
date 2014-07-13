#include <stdio.h>
#include <iostream>

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
            j1->gererEvenement(e);
        }

        j1->update(projectiles);
        for(Uint8 i(0); i < projectiles.size(); i++) {
            projectiles[i]->deplacer();
        }

        std::vector<int> aDetruire;
        for(Uint8 i(0); i < projectiles.size(); i++) {
            if(projectiles[i]->isHorsEcran()) {
                aDetruire.push_back(i);
            }
        }
        for(int i(0); i < (int)aDetruire.size(); i++) {
            std::cout << "Destruction du projectile : " << i << " : ";
            delete projectiles[i];
            projectiles.erase(projectiles.begin()+i);
        }
        aDetruire.clear();

        SDL_RenderClear(Utils::renderer);

        j1->render();
        for(Uint8 i(0); i < projectiles.size(); i++) {
            projectiles[i]->render();
        }

        SDL_RenderPresent(Utils::renderer);

    }
    delete j1;
    j1 = NULL;
    return 0;
}
