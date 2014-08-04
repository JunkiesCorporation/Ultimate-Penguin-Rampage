#include <stdio.h>
#include <iostream>

#include "Jeu.h"
#include "Utils.h"
#include "Enums.h"
#include "Constantes.h"

std::vector<Projectile*> Jeu::projectiles(0);

// Construceur
Jeu::Jeu() {
    m_j1 = new Joueur();
    m_carte = new Carte("map/test_1.txt");
    m_camera.x = 0; m_camera.y = 0;
    m_camera.w = LARGEUR_ECRAN; m_camera.h = HAUTEUR_ECRAN;
    start();
}

// Destructeur
Jeu::~Jeu() {
    delete m_j1; m_j1 = NULL;
    delete m_carte; m_carte = NULL;
}

// Gère tout le jeu
int Jeu::start() {
    printf("Jeu lance.\n");
    bool quit(false);
    SDL_Event e;

    //m_carte->render();

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
    // Gestion du joueur
    m_j1->update(*m_carte);

    // Gestion de la caméra
    m_camera.x = m_j1->getPos().x + (m_j1->getLargeur()/2) - (LARGEUR_ECRAN/2);
    m_camera.y = m_j1->getPos().y + (m_j1->getHauteur()/2) - (HAUTEUR_ECRAN/2);

    // Gestion des projectiles
    for(int i(0); i < (int)Jeu::projectiles.size(); i++) {
        Jeu::projectiles[i]->update(*m_carte);
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

    m_carte->render(m_camera);

    for(Uint8 i(0); i < Jeu::projectiles.size(); i++) {
        Jeu::projectiles[i]->render(m_camera);
    }

    m_j1->render(m_camera);

    SDL_RenderPresent(Utils::renderer);
}
