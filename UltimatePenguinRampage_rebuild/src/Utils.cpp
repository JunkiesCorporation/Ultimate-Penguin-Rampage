﻿#include <iostream>

#include "UPR.h"
#include "Utils.h"

// Fonctions membres publiques
//-------------------------------------
/* Initialise la SDL et ses principaux composants.*/
bool Utils::initialisationSDL()
{
	// Si oui ou non l'initialisation de la SDL a réussie.
	bool succes = true;
	
	//---------------------------------
	
	// Initialisation des composants requis de la SDL et gestion d'un échec potentiel.
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur : Impossible d'initialiser la SDL." << std::endl;
		succes = false;
	}
	else
	{
		// Tentative de création de la fenêtre.
		UPR::fenetre_SDL = SDL_CreateWindow("Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
		
		// Gestion d'un échec potentiel.
		if(UPR::fenetre_SDL == NULL)
		{
			std::cout << "Erreur : Echec de la creation de la fenetre." << std::endl;
			succes =  false;
		}
		else
		{
			// Tentative de création du renderer.
			UPR::renderer_SDL = SDL_CreateRenderer(UPR::fenetre_SDL, -1, SDL_RENDERER_ACCELERATED);
			
			// Gestion d'un échec potentiel.
			if(UPR::renderer_SDL == NULL)
			{
				std::cout << "Erreur : Echec de la creation du renderer." << std::endl;
				succes = false;
			}
			else
			{
				// Réglage de la couleur par défaut à noire.
				SDL_SetRenderDrawColor(UPR::renderer_SDL, 0, 0, 0, 255);
				
				// Assouplissement du changement d'échelle.
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
				
				// Changement de la taille logique.
				SDL_RenderSetLogicalSize(UPR::renderer_SDL, UPR::LARGEUR_ECRAN, UPR::HAUTEUR_ECRAN);
			}
		}
	}
	
	return succes;
}

/* Détruit les composants restants de la SDL et quitte correctement les systèmes ouverts.*/
void Utils::quitterSDL()
{
	// Destruction de UPR::renderer_SDL.
	SDL_DestroyRenderer(UPR::renderer_SDL);
	// Destruction de UPR::fenetre_SDL.
	SDL_DestroyWindow(UPR::fenetre_SDL);
	
	// Rend les pointeurs inutilisables.
	UPR::renderer_SDL = NULL;
	UPR::fenetre_SDL = NULL;
	
	// Fermeture des systèmes ouverts
	SDL_Quit();
}

/* Constructeur par défaut.*/
Timer::Timer() : m_ticks_depart(0)
{
	
}

/* Démarre le Timer.*/
void Timer::start()
{
	// On récupère le temps système actuel.
	m_ticks_depart = SDL_GetTicks();
}

/* Retourne le nombre de ticks écoulé depuis le démarrage du Timer.*/
Uint32 Timer::getTicks()
{
	return SDL_GetTicks() - m_ticks_depart;
}
//-------------------------------------