#include <stdio.h>
#include <SDL.h>
#include <iostream>

#include "Utils.h"
#include "Jeu.h"

int main(int argc, char* args[]) {
    // Initialisation du programme
    if(!Utils::initialisation()) {
        std::cout << "Une Erreur est survenue lors de l'initialisation du programme : " << std::endl;
        std::cout << "SDL_Error: %s" << SDL_GetError() << std::endl;
        return -1;
    }

    bool quit(false); // Variable de contrôle de la boucle principale
    SDL_Event e; // Objet permettant de gérer les événements

    Jeu jeu; // Lancement du jeu;

    // Boucle principale du programme
    while(!quit) {
        // Affichage et gestion du menu principal
        // Démarrage du jeu
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    Utils::quitter();

	return 0;
}
