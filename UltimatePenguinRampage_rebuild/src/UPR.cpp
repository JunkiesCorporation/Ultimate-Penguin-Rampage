#include <iostream>

#include "UPR.h"
#include "Utils.h"

SDL_Window* UPR::fenetre_SDL = NULL;
SDL_Renderer* UPR::renderer_SDL = NULL;

/** La fonction main.
 *
 * Initialise la SDL grâces aux méthodes static de la
 * classe Utils, lance la cinématique d'introduction puis le
 * menu principal.
 * 
 * Une fois le jeu quitté, quitte la SDL correctement grâce à Utils::quitter().
 */
int main(int argc, char* args[])
{
	bool quit = false; // Contrôle de la boucle principale.
	
	// Initialisation de la SDL.
	if(!Utils::initialisationSDL())
	{
		std::cout << "Une erreur est survenue lors de l'initialisation de la SDL : " << std::endl;
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		std::cout << "Le programme va s'arreter." << std::endl;
		return -1;
	}
	
	while(!quit)
	{
		SDL_Delay(2000);
		
		quit = true;
	}
	
	Utils::quitter();
	
	return 0;
}