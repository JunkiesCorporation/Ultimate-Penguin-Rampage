#include <stdio.h>
#include <SDL.h>
#include "UPR.h"

//Dimensions de l'�cran
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool SDLInit(SDL_Window*, SDL_Surface*);
void SDLQuit(SDL_Window*);

int main(int argc, char* args[]) {
	SDL_Window* window = NULL; // Fen�tre du programme
	SDL_Surface* screenSurface = NULL; // La surface contenue dans la fen�tre

	if(!SDLInit(window, screenSurface)) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
	}
    screenSurface = SDL_GetWindowSurface(window); // R�cup�ration de la surface � partir de la fen�tre cr��e
    SDL_Delay( 2000 );
    printf("plop");

    SDLQuit(window);

	return 0;
}

// Initialise la SDL et retourne true si il n'y a pas d'erreur
bool SDLInit(SDL_Window *window, SDL_Surface *screenSurface) {
    SDL_DestroyWindow(window);
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) // Initialise la SDL
	{
		return false;
	}
	else
	{
		// Cr�� la fen�tre
		window = SDL_CreateWindow( "Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			return false;
		}
	}
	return true;
}

// Quite la SDL proprement
void SDLQuit(SDL_Window *window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
