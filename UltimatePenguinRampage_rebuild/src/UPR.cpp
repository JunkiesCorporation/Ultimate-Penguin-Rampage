#include <iostream>

#include "Texture.h"
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
	
	//---------------------------------
	
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

/* Gère l'affichage et le contrôle du menu principal.*/
int gestionMenuPrincipal()
{
	// Choix à retourner.
	int choix = -1;
	
	// Chemins des images du menu.
	char chemin_image_fond[] = "img/menu_principal/menu_principal.bmp";
	
	// Textures contenant les images du menu.
	Texture* texture_fond = NULL;
	
	//---------------------------------
	
	// Tentative de chargement de l'image de fond.
	SDL_Surface* surface_image_fond = SDL_LoadBMP(chemin_image_fond);
	
	// Gestion d'un échec potentiel.
	if(surface_image_fond == NULL)
	{
		std::cout << "Erreur : Impossible de charger l'image " << chemin_image_fond << " :" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		choix = -1;
	}
	else
	{
		/* Test avec Texture et render en boucle */
		int compteur = 0;
		SDL_Texture* texture_test = NULL;
		
		// Creation de la texture
		texture_test = SDL_CreateTextureFromSurface(UPR::renderer_SDL, surface_image_fond);
		
		SDL_RenderClear(UPR::renderer_SDL);
		SDL_RenderCopy(UPR::renderer_SDL, texture_test, NULL, NULL);
		SDL_RenderPresent(UPR::renderer_SDL);
		
		std::cout << SDL_GetTicks() << std::endl;
		
		SDL_Delay(2000);
		
		// Libération des surfaces chargées.
		SDL_DestroyTexture(texture_test);
		SDL_FreeSurface(surface_image_fond);
		// SDL_FreeSurface(image_optimisee);
		
		texture_test = NULL;
		surface_image_fond = NULL;
		// image_optimisee = NULL;
	}
	
	return choix;
}