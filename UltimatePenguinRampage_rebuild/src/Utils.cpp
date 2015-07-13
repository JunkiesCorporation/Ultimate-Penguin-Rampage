#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

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
		UPR::fenetre_SDL = SDL_CreateWindow("Ultimate Penguin Rampage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, UPR::LARGEUR_ECRAN, UPR::HAUTEUR_ECRAN, SDL_WINDOW_SHOWN);
		
		// Gestion d'un échec potentiel.
		if(UPR::fenetre_SDL == NULL)
		{
			std::cout << "Erreur : Echec de la creation de la fenetre." << std::endl;
			succes =  false;
		}
		else
		{
			// Tentative de création du renderer.
			UPR::renderer_SDL = SDL_CreateRenderer(UPR::fenetre_SDL, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
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
//-------------------------------------

// Fonctions globales
//-------------------------------------
/* Converti le nombre donnée en un objet string qui contient sa représentation en texte.*/
std::string intVersString(int const &p_nombre)
{
	// String à retourner.
	std::string nombre_string;
	
	// Le flux string qui permet de convertir.
	std::stringstream ss;
	
	//---------------------------------
	// Conversion du nombre;
	ss << p_nombre;
	nombre_string = ss.str();
	
	return nombre_string;
}

/* Remplace tous les tirets bas '_' par des espaces ' ' dans le texte donné.*/
std::string remplacerParEspaces(std::string const &p_texte)
{
	// String à retourner.
	std::string nouveau_texte = p_texte;
	
	//---------------------------------
	// Remplacement des tirets bas.
	std::replace(nouveau_texte.begin(), nouveau_texte.end(), '_', ' ');
	
	return nouveau_texte;
}
//-------------------------------------