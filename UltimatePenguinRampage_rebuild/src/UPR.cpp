﻿#include <iostream>

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
	// Contrôle de la boucle principale.
	bool quit = false; 
	
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
		gestionMenuPrincipal();
		
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
	
	// Contrôle de la boucle du menu.
	bool quit = false;
	
	/* Liste des images :
	 * - image de fond
	 * - image nouveau profil
	 * - image charger profil
	 * - image mode LAN
	 * - image options
	 * - image quitter
	 * - image curseur de sélection
	 */
	
	// Chemins des images du menu.
	char chemin_image_fond[] = "img/menu_principal/menu_principal.bmp";
	
	// Textures contenant les images du menu.
	Texture* texture_fond = NULL;
	
	// Élément de manipulations des événements.
	SDL_Event e;
	
	//---------------------------------
	
	// Chargement des images du menu.
	texture_fond = new Texture(chemin_image_fond);
	
	// Boucle du menu.
	while(!quit)
	{
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		// Render des images du menu.
		texture_fond->render(0, 0);
		
		// Affichage à l'écran.
		SDL_RenderPresent(UPR::renderer_SDL);
		
		// Gestion des événements.
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}
	}
	
	// Libération des images du menu.
	texture_fond->liberer();
	texture_fond = NULL;
	
	return choix;
}