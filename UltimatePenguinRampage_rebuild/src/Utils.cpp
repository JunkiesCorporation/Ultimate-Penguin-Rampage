#include <iostream>

#include "UPR.h"
#include "Utils.h"

bool Utils::initialisationSDL()
{
	bool succes = true; ///< Si oui ou non l'initialisation a réussie
	
	// Initialisation des composants requis de la SDL et gestion d'un échec potentiel
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur : Impossible d'initialiser la SDL." << std::endl;
		succes = false;
	}
	else
	{
		// Tentative de création de la _fenetre_SDL_ 
		UPR::fenetre_SDL = SDL_CreateWindow("Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, UPR::LARGEUR_ECRAN, UPR::HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);
		
		// Gestion d'un échec potentiel
		if(UPR::fenetre_SDL == NULL)
		{
			std::cout << "Erreur: Echec de la creation de la fenetre." << std::endl;
			succes =  false;
		}
		else
		{
			// Récupération de la surface de _fenetre_SDL_
			UPR::surface_ecran = SDL_GetWindowSurface(UPR::fenetre_SDL);
		}
	}
	
	return succes;
}

void Utils::quitter()
{
	// Destruction de _fenetre_SDL_
	SDL_DestroyWindow(UPR::fenetre_SDL);
	
	// Fermeture des systèmes ouverts
	SDL_Quit();
}