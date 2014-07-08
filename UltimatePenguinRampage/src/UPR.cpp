#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include "UPR.h"

//Dimensions de l'écran
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool SDLInit(SDL_Window**, SDL_Surface**);
void SDLQuit(SDL_Window**, SDL_Surface**);

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* penguin = NULL;

	if(!SDLInit(&window, &screenSurface)) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
	}

	penguin = SDL_LoadBMP("img/PBface.bmp");
	if(penguin == NULL) {
        printf("plop");
	}

	SDL_BlitSurface(penguin, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);

    bool quit(false);
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDLQuit(&window, &penguin);

	return 0;
}

// Initialise la SDL et retourne true si il n'y a pas d'erreur
bool SDLInit(SDL_Window** window, SDL_Surface** screenSurface) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) // Initialise la SDL
	{
		return false;
	}
	else
	{
		// Créé la fenêtre
		*window = SDL_CreateWindow( "Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(*window == NULL )
		{
			return false;
		} else {
		    *screenSurface = SDL_GetWindowSurface(*window); // Récupération de la surface à partir de la fenêtre créée
		}
	}
	return true;
}

// Quite la SDL proprement
void SDLQuit(SDL_Window** window, SDL_Surface** penguin) {
    SDL_FreeSurface(*penguin); *penguin = NULL;
    SDL_DestroyWindow(*window); *window = NULL;
    SDL_Quit();
}
