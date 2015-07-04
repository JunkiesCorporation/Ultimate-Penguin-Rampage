#include <iostream>
#include <string.h>

#include "Jeu.h"
#include "Struct.h"
#include "UPR.h"

/* Constructeur par défaut.*/
Jeu::Jeu()
{
	// Initialisation des attributs à des valeurs par défaut.
	// Initialisation des pointeurs vers les textures individuelles à NULL.
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_fond_mode_histoire = NULL;
	// Initialisation des pointeurs vers les textures contenues dans des tableaux à NULL.
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		m_textures_options_ecran_jeu[i] = NULL;
	}
	
	ticks_image = 0;
}

/* Destructeur par défaut.*/
Jeu::~Jeu()
{
	// Suppression des textures qui auraient été oubliées.
	delete m_texture_cadre_selection;
	delete m_texture_fond_jeu;
	delete m_texture_fond_mode_histoire;
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		delete m_textures_options_ecran_jeu[i];
	}
	
	// Fermeture des pointeurs.
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_fond_mode_histoire = NULL;
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		m_textures_options_ecran_jeu[i] = NULL;
	}
}

// Fonctions membres publiques
//-------------------------------------
/* Affiche l'écran principal du jeu et permet la navigation vers les fonctionnalités du jeu.*/
void Jeu::lancer(Profil* profil_joueur)
{
	// Contrôle de la boucle de l'écran principal du jeu.
	bool quit = false;
	
	// Chemin d'accès à l'image du curseur de sélection.
	char chemin_image_cadre_selection[] = "img/jeu/jeu_cadre_selection.bmp";
	
	// La position actuelle du curseur.
	EnumOptionsEcranPrincipal position_curseur_act = MODE_HISTOIRE;
	
	// La position précédente du curseur.
	EnumOptionsEcranPrincipal position_curseur_prec = MODE_HISTOIRE;
	
	// Positions des images de l'écran principal du jeu.
	Position positions_textures_ecran[NB_OPTIONS] = {{0, 0}};
	
	// Positions du curseur lors de l'écran principal du jeu.
	Position positions_curseur_ecran[NB_OPTIONS] = {{0, 0}};
	
	//---------------------------------
	
	// Chargement des images de l'écran principal du jeu.
	chargerTexturesEcran();
	
	// Chargement de l'image du curseur de sélection.
	m_texture_cadre_selection = new Texture(chemin_image_cadre_selection);

	
	// Attribution des positions des images de l'écran principal du jeu.
	positions_textures_ecran[MODE_HISTOIRE] = {120, 250};
	positions_textures_ecran[MODE_ARENE] = {530, 250};
	positions_textures_ecran[RETOUR_MENU] = {325, 480};
	
	// Attribution des positions du curseur lors de l'écran principal du jeu.
	positions_curseur_ecran[MODE_HISTOIRE] = {115, 245};
	positions_curseur_ecran[MODE_ARENE] = {525, 245};
	positions_curseur_ecran[RETOUR_MENU] = {320, 475};
	
	// Boucle de l'écran principal du jeu.
	while(!quit)
	{
		// Début du chronométrage de l'image.
		timer.start();
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		// Affichage des images fixes de l'écran principal du jeu.
		m_texture_fond_jeu->render(0, 0);
		for(int i = 0; i < NB_OPTIONS; i++)
		{
			m_textures_options_ecran_jeu[i]->render(positions_textures_ecran[i]);
		}
		
		// Affichage du curseur lors de l'écran principal du jeu.
		m_texture_cadre_selection->render(positions_curseur_ecran[position_curseur_act]);
		
		// Affichage à l'écran.
		SDL_RenderPresent(UPR::renderer_SDL);
		
		// Gestion des événements.
		while(SDL_PollEvent(&e) != 0)
		{
			// Si une touche est appuyée.
			if(e.type == SDL_KEYDOWN)
			{
				// Switch sur le symbole de la touche appuyée.
				switch(e.key.keysym.sym)
				{
				// La touche "flèche_droite" est appuyée.
				case SDLK_RIGHT:
					// Changement de la position du curseur.
					if(position_curseur_act == MODE_HISTOIRE)
					{
						position_curseur_prec = MODE_HISTOIRE;
						position_curseur_act = MODE_ARENE;
					}
					break;
				
				// La touche "flèche_gauche" est appuyée.
				case SDLK_LEFT:
					// Changement de la position du curseur.
					if(position_curseur_act == MODE_ARENE)
					{
						position_curseur_prec = MODE_ARENE;
						position_curseur_act = MODE_HISTOIRE;
					}
					break;
				
				// La touche "flèche_bas" est appuyée.
				case SDLK_DOWN:
					// Changement de la position du curseur.
					if(position_curseur_act == MODE_ARENE || position_curseur_act == MODE_HISTOIRE)
					{
						position_curseur_prec = position_curseur_act;
						position_curseur_act = RETOUR_MENU;
					}
					break;
				
				// La touche "flèche_haut" est appuyée.
				case SDLK_UP:
					// Changement de la position du curseur.
					if(position_curseur_act == RETOUR_MENU)
					{
						position_curseur_act = position_curseur_prec;
						position_curseur_prec = RETOUR_MENU;
					}
					break;
				
				// La touche "retour" est appuyée.
				case SDLK_RETURN:
					// Agissement en fonction de la position du curseur.
					switch(position_curseur_act)
					{
					// Si l'utilisateur choisi le mode histoire.
					case MODE_HISTOIRE:
						// Libération des images de l'écran principal du jeu.
						libererTexturesEcran();
						
						// Lancement du mode histoire avec le profil du joueur.
						modeHistoire(profil_joueur);
						
						// Chargement des images de l'écran principal du jeu une fois le mode histoire terminé.
						chargerTexturesEcran();
						break;
					
					// Si l'utilisateur choisi de retourner au menu principal.
					case RETOUR_MENU:
						// Quitte le jeu sans confirmation.
						quit = true;
						break;
					}
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
	
	delete m_texture_cadre_selection;
	m_texture_cadre_selection = NULL;
	
	// Libération des images de l'écran principal du jeu.
	libererTexturesEcran();
}
//-------------------------------------

// Fonctions membres privées
//-------------------------------------
/* Charge les textures nécessaires à l'écran principal du jeu.*/
void Jeu::chargerTexturesEcran()
{
	// Chemins des images à charger.
	char chemin_image_fond_jeu[] = "img/jeu/jeu_image_fond.bmp";
	std::string chemin_images_ecran_jeu[NB_OPTIONS] =
	{
		"img/jeu/jeu_mode_histoire.bmp",
		"img/jeu/jeu_mode_arene.bmp",
		"img/jeu/jeu_retour_menu_principal.bmp"
	};
	
	// Chargement des textures.
	m_texture_fond_jeu = new Texture(chemin_image_fond_jeu);
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		m_textures_options_ecran_jeu[i] = new Texture(chemin_images_ecran_jeu[i].c_str());
	}
}

/* Charge les textures nécessaires à l'écran du mode histoire.*/
void Jeu::chargerTexturesModeHistoire()
{
	// Chemins des images à charger.
	char chemin_image_fond_mode_histoire[] = "img/jeu/mode_histoire/mode_histoire_image_fond.bmp";
	
	// Chargement des textures.
	m_texture_fond_mode_histoire = new Texture(chemin_image_fond_mode_histoire);
}

/* Libère les textures de l'écran principal du jeu.*/
void Jeu::libererTexturesEcran()
{
	// Suppression des textures.
	delete m_texture_fond_jeu;
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		delete m_textures_options_ecran_jeu[i];
	}
	
	// Fermeture des pointeurs.
	m_texture_fond_jeu = NULL;
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		m_textures_options_ecran_jeu[i] = NULL;
	}
}

/* Libère les textures de l'écran du mode histoire.*/
void Jeu::libererTexturesModeHistoire()
{
	// Suppression des textures.
	delete m_texture_fond_mode_histoire;
	
	// Fermeture des pointeurs.
	m_texture_fond_mode_histoire = NULL;
}

/* Affiche et gère le mode histoire.*/
void Jeu::modeHistoire(Profil* profil_joueur)
{
	// Contrôle de la boucle de sélection de niveau.
	bool quit = false;
	
	//---------------------------------
	
	// Chargement des images du mode histoire.
	chargerTexturesModeHistoire();
	
	// Initialisation des ticks image.
	ticks_image = 0;
	
	// Boucle de sélection de niveau.
	while(!quit)
	{
		// Début du chronométrage de l'image.
		timer.start();
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		// Affichage de l'image de fond de la sélection du niveau.
		m_texture_fond_mode_histoire->render(0, 0);
		
		// Affichage à l'écran.
		SDL_RenderPresent(UPR::renderer_SDL);
		
		/** \todo Navigation parmi les arènes disponibles dans le mode histoire. */
		
		// Gestion des événements.
		while(SDL_PollEvent(&e) != 0)
		{
			// Si une touche est appuyée.
			if(e.type == SDL_KEYDOWN)
			{
				// Switch sur le symbole de la touche appuyée.
				switch(e.key.keysym.sym)
				{
				// La touche "retour" est appuyée.
				case SDLK_RETURN:
					// Libération des images du mode histoire pour alléger la mémoire.
					libererTexturesModeHistoire();
					
					// Chargement de l'arène choisie
					m_arene.charger();
					
					// Lancement de l'arène chargée.
					m_arene.lancer();
					
					// Ré-initialisation de l'arène terminée.
					m_arene.reinitialiser();
					
					// Chargement des images du mode histoire avant le retour à la navigation.
					chargerTexturesModeHistoire();
					break;
				
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
	
	// Libération des images du mode histoire.
	libererTexturesModeHistoire();
}
//-------------------------------------