#include <iostream>

#include "Texture.h"
#include "UPR.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Texture::Texture() : m_image(NULL), m_largeur(0), m_hauteur(0)
{
	
}

/* Constructeur avec chemin d'image.*/
Texture::Texture(const char* chemin_image) : m_image(NULL), m_largeur(0), m_hauteur(0)
{
	charger(chemin_image);
}
//-------------------------------------

// Destructeur
//-------------------------------------
Texture::~Texture()
{
	liberer();
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Charge l'image située au chemin donné.*/
void Texture::charger(const char* chemin_image)
{
	// La nouvelle texture
	SDL_Texture* nouvelle_texture = NULL;
	
	// L'image chargée avant création de la texture.
	SDL_Surface* image_chargee = NULL;
	
	//---------------------------------
	
	// Libération de l'éventuelle Texture précédente.
	liberer();
	
	// Tentative de chargement de l'image Bitmap.
	image_chargee = SDL_LoadBMP(chemin_image);
	
	// Gestion d'un échec potentiel.
	if(image_chargee == NULL)
	{
		std::cout << "Erreur : l'image " << chemin_image << " n'a pas pu etre chargee." << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	else
	{
		// Activation de la transparence.
		SDL_SetColorKey(image_chargee, SDL_TRUE, SDL_MapRGB(image_chargee->format, 255, 0, 255));
		
		// Tentative de création de la texture.
		nouvelle_texture = SDL_CreateTextureFromSurface(UPR::renderer_SDL, image_chargee);
		
		// Gestion d'un échec potentiel.
		if(nouvelle_texture == NULL)
		{
			std::cout << "Erreur : La texture n'a pas pu etre creee." << std::endl;
		}
		else
		{
			// Récupération de la largeur de l'image chargée.
			m_largeur = image_chargee->w;
			
			// Récupération de la hauteur de l'image chargée.
			m_hauteur = image_chargee->h;
		}
		
		// Libération de l'image chargée afin de ne pas encombrer la mémoire, et fermeture du pointeur.
		SDL_FreeSurface(image_chargee);
		image_chargee = NULL;
	}
	
	// Attribution de la nouvelle texture, chargée ou non.
	m_image = nouvelle_texture;
}

/* Libère la Texture.*/
void Texture::liberer()
{
	if(m_image != NULL)
	{
		// Destruction de l'image.
		SDL_DestroyTexture(m_image);
		
		// Ré-initialisation des membres en vue d'une réutilisation éventuelle.
		m_image = NULL;
		m_largeur = 0;
		m_hauteur = 0;
	}
}
//-------------------------------------