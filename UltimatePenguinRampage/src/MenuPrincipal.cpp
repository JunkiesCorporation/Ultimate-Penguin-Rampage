#include <SDL.h>

#include "MenuPrincipal.h"
#include "Utils.h"

///temp
#include <iostream>

SDL_Surface* MenuPrincipal::m_menu_principal = NULL;

int MenuPrincipal::menuPrincipal() {
	int choix(0); ///< Le choix de l'utilisateur.
	bool quit(false);
	SDL_Event e;
	
	// Chargement des images nécessaires au menu
	chargerTextures();
	
	// TEMP
	std::cout << "Textures du menu principal chargees." << std::endl;
	
	// Chargement de l'image principale sur le back buffer
	SDL_BlitSurface(MenuPrincipal::m_menu_principal, NULL, Utils::screenSurface, NULL);
	
	// M-à-j de la fenêtre
	SDL_UpdateWindowSurface(Utils::fenetre);
	
	SDL_Delay(2000);
	
	// Suppression des images chargées pour le menu
	supprimerTextures();
	
	return choix;
}

void MenuPrincipal::chargerTextures() {
	MenuPrincipal::m_menu_principal = SDL_LoadBMP("img/menu_principal/menu_principal.bmp");
	
	if( MenuPrincipal::m_menu_principal == NULL )
    {
        std::cout<< "Unable to load image " << "img/menu_principal/menu_principal.bmp" << "! SDL Error: " << SDL_GetError() << std::endl;
    }
}

void MenuPrincipal::supprimerTextures() {
	SDL_FreeSurface(MenuPrincipal::m_menu_principal);
	MenuPrincipal::m_menu_principal = NULL;
}