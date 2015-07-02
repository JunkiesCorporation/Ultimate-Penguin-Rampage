#include <iostream>

#include "Jeu.h"
#include "Struct.h"
#include "Timer.h"
#include "UPR.h"

/* Constructeur par défaut.*/
Jeu::Jeu()
{
	// Réglage des pointeurs vers les Textures à NULL.
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_mode_histoire = NULL;
	
	// temp
	std::cout << "Jeu instancie." << std::endl;
}

/* Destructeur par défaut.*/
Jeu::~Jeu()
{
	// Suppression des textures qui auraient été oubliées.
	delete m_texture_cadre_selection;
	delete m_texture_fond_jeu;
	delete m_texture_mode_histoire;
	
	// Fermeture des pointeurs.
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_mode_histoire = NULL;
	
	// temp
	std::cout << "Jeu detruit." << std::endl;
}

/* Lance le jeu avec les données du Profil donné.*/
void Jeu::lancer(Profil* profil_joueur)
{
	// Contrôle de la boucle du Jeu.
	bool quit = false;
	
	// Nombre d'images de l'écran principal du jeu : 2
	// Positions des images de l'écran principal du jeu.
	Position positions_textures_ecran[2] = {{0, 0}};
	
	// Positions du curseur lors de l'écran principal du jeu.
	Position positions_curseur_ecran[1] = {{0, 0}};
	
	// Élément de manipulations des événements.
	SDL_Event e;
	
	// Timer pour bloquer les FPS à 60 et nombre ticks par image.
	Timer timer;
	int ticks_image = 0;
	
	//---------------------------------
	
	// temp
	std::cout << "Jeu lance avec le profil : " << profil_joueur->getNomProfil() << std::endl;
	
	// Chargement des images de l'écran principal du jeu.
	chargerTexturesEcran();
	
	// Attribution des positions des images de l'écran principal du jeu.
	positions_textures_ecran[0] = {0, 0}; // m_texture_fond_jeu
	positions_textures_ecran[1] = {120, 250}; // m_texture_mode_histoire
	
	// Attribution des positions du curseur lors de l'écran principal du jeu.
	positions_curseur_ecran[0] = {115, 245}; // sur m_texture_mode_histoire
	
	// Boucle du jeu.
	
	while(!quit)
	{
		// Début du chronométrage de l'image.
		timer.start();
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		// Affichage des images fixes de l'écran principal du jeu.
		m_texture_fond_jeu->render(positions_textures_ecran[0]);
		m_texture_mode_histoire->render(positions_textures_ecran[1]);
		
		// Affichage du curseur lors de l'écran principal du jeu.
		m_texture_cadre_selection->render(positions_curseur_ecran[0]);
		
		// Affichage à l'écran.
		SDL_RenderPresent(UPR::renderer_SDL);
		
		while(SDL_PollEvent(&e) != 0)
		{
			// Si une touche est appuyée.
			if(e.type == SDL_KEYDOWN)
			{
				// Switch sur le symbole de la touche appuyée.
				switch(e.key.keysym.sym)
				{
				// La touche "q" est appuyée.
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}
		
		// Correction si le FPS dépasse le maximum.
		ticks_image = timer.getTicks();
		if(ticks_image < UPR::TICKS_ECRAN_PAR_IMAGE)
		{
			SDL_Delay(UPR::TICKS_ECRAN_PAR_IMAGE - ticks_image);
		}
	}
	
	
	libererTexturesEcran();
	
	// temp
	std::cout << "Jeu termine, retour au menu principal." << std::endl << std::endl;
}

void Jeu::chargerTexturesEcran()
{
	char chemin_image_cadre_selection[] = "img/jeu/jeu_cadre_selection.bmp";
	char chemin_image_fond_jeu[] = "img/jeu/jeu_image_fond.bmp";
	char chemin_image_mode_histoire[] = "img/jeu/jeu_mode_histoire.bmp";
	
	m_texture_cadre_selection = new Texture(chemin_image_cadre_selection);
	m_texture_fond_jeu = new Texture(chemin_image_fond_jeu);
	m_texture_mode_histoire = new Texture(chemin_image_mode_histoire);
}

void Jeu::libererTexturesEcran()
{
	delete m_texture_cadre_selection;
	delete m_texture_fond_jeu;
	delete m_texture_mode_histoire;
	
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_mode_histoire = NULL;
}