#include <iostream>

#include "UPR.h"
#include "Utils.h"

SDL_Window* UPR::fenetre_SDL = NULL;
SDL_Surface* UPR::surface_ecran = NULL;

int main(int argc, char* args[]) {
	
	// Initialisation de la SDL
	if(!Utils::initialisationSDL()) {
		std::cout << "Une erreur est survenue lors de l'initialisation de la SDL : " << std::endl;
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		std::cout << "Le programme va s'arreter." << std::endl;
		return -1;
	}
	
	Utils::quitter();
	
	return 0;
}