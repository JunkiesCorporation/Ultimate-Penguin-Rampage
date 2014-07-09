#include <stdio.h>
#include <SDL.h>
#include "UPR.h"
#include "Jeu.h"

//Dimensions de l'écran
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool SDLInit(SDL_Window**, SDL_Surface**);
void SDLQuit(SDL_Window**);

int main(int argc, char* args[]) {
    SDL_Window* fenetre = NULL; // Pointeur vers la fenêtre du programme
    SDL_Surface* ecran = NULL; // Pointeur vers le contenu de la fenêtre

    // Initialisation de la SDL
	if(!SDLInit(&fenetre, &ecran)) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
	}

    // Boucle principale du programme
    bool quit(false);
    SDL_Event e; // Objet permettant de gérer les événements

    Jeu jeu(fenetre, ecran); // Instanciation d'un objet Jeu. C'est là-dedans que le jeu se déroule

    while(!quit) {
        // Affichage et gestion du menu principal
        // Démarrage du jeu
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDLQuit(&fenetre);

	return 0;
}

// Initialise la SDL et retourne true si il n'y a pas d'erreur
bool SDLInit(SDL_Window** fenetre, SDL_Surface** ecran) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) // Initialise la SDL
	{
		return false;
	}
	else
	{
		// Créé la fenêtre
		*fenetre = SDL_CreateWindow( "Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(*fenetre == NULL )
		{
			return false;
		} else {
		    *ecran = SDL_GetWindowSurface(*fenetre); // Récupération de la surface à partir de la fenêtre créée
		}
	}
	return true;
}

// Quite la SDL proprement
void SDLQuit(SDL_Window** fenetre) {
    SDL_DestroyWindow(*fenetre); *fenetre = NULL;
    SDL_Quit();
}
