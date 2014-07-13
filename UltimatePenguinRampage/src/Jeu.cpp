#include <stdio.h>
#include <iostream>

#include "Jeu.h"
#include "Projectile.h"
#include "Utils.h"
#include "Enums.h"

std::vector<Projectile*> Jeu::projectiles(0);

// Construceur
Jeu::Jeu() {
    m_j1 = new Joueur();
    start();
}

// Destructeur
Jeu::~Jeu() {
    delete m_j1;
    m_j1 = NULL;
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
            m_j1->gererEvenement(e);
        }

        update();

        render();
    }
    return 0;
}

void Jeu::update() {
    m_j1->update();

    for(int i(0); i < (int)Jeu::projectiles.size(); i++) {
        Jeu::projectiles[i]->update();
    }

    std::vector<int> aDetruire(0);
    for(int i(0); i < (int)Jeu::projectiles.size(); i++) {
        if(Jeu::projectiles[i]->isHorsEcran()) {
            aDetruire.push_back(i);
        }
    }
    for(int i(0); i < (int)aDetruire.size(); i++) {
        delete Jeu::projectiles[aDetruire[i]];
        Jeu::projectiles.erase(Jeu::projectiles.begin()+aDetruire[i]);
    }
    aDetruire.clear();
}

void Jeu::render() {
    SDL_RenderClear(Utils::renderer);

    for(Uint8 i(0); i < Jeu::projectiles.size(); i++) {
        Jeu::projectiles[i]->render();
    }

    m_j1->render();

    SDL_RenderPresent(Utils::renderer);
}
