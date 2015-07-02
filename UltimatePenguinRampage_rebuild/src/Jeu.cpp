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
	m_texture_mode_arene = NULL;
	m_texture_mode_histoire = NULL;
	m_texture_retour_menu = NULL;
}

/* Destructeur par défaut.*/
Jeu::~Jeu()
{
	// Suppression des textures qui auraient été oubliées.
	delete m_texture_cadre_selection;
	delete m_texture_fond_jeu;
	delete m_texture_mode_arene;
	delete m_texture_mode_histoire;
	delete m_texture_retour_menu;
	
	// Fermeture des pointeurs.
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_mode_arene = NULL;
	m_texture_mode_histoire = NULL;
	m_texture_retour_menu = NULL;
}

/* Lance le jeu avec les données du Profil donné.*/
void Jeu::lancer(Profil* profil_joueur)
{
	// Contrôle de la boucle du Jeu.
	bool quit = false;
	
	// La position actuelle du curseur.
	enum_ecran_options position_curseur_act = MODE_HISTOIRE;
	
	// La position précédente du curseur.
	enum_ecran_options position_curseur_prec = MODE_HISTOIRE;
	
	// Positions des images de l'écran principal du jeu.
	Position positions_textures_ecran[NB_OPTIONS] = {{0, 0}};
	
	// Positions du curseur lors de l'écran principal du jeu.
	Position positions_curseur_ecran[NB_OPTIONS] = {{0, 0}};
	
	// Élément de manipulations des événements.
	SDL_Event e;
	
	// Timer pour bloquer les FPS à 60 et nombre ticks par image.
	Timer timer;
	int ticks_image = 0;
	
	//---------------------------------
	
	// Chargement des images de l'écran principal du jeu.
	chargerTexturesEcran();
	
	// Attribution des positions des images de l'écran principal du jeu.
	positions_textures_ecran[MODE_HISTOIRE] = {120, 250};
	positions_textures_ecran[MODE_ARENE] = {530, 250};
	positions_textures_ecran[RETOUR_MENU] = {325, 480};
	
	// Attribution des positions du curseur lors de l'écran principal du jeu.
	positions_curseur_ecran[MODE_HISTOIRE] = {115, 245};
	positions_curseur_ecran[MODE_ARENE] = {525, 245};
	positions_curseur_ecran[RETOUR_MENU] = {320, 475};
	
	// Boucle du jeu.
	while(!quit)
	{
		// Début du chronométrage de l'image.
		timer.start();
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		// Affichage des images fixes de l'écran principal du jeu.
		m_texture_fond_jeu->render(0, 0);
		m_texture_mode_histoire->render(positions_textures_ecran[MODE_HISTOIRE]);
		m_texture_mode_arene->render(positions_textures_ecran[MODE_ARENE]);
		m_texture_retour_menu->render(positions_textures_ecran[RETOUR_MENU]);
		
		// Affichage du curseur lors de l'écran principal du jeu.
		m_texture_cadre_selection->render(positions_curseur_ecran[position_curseur_act]);
		
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
				// La touche "flèche_droite" est appuyée.
				case SDLK_RIGHT:
					if(position_curseur_act == MODE_HISTOIRE)
					{
						position_curseur_prec = MODE_HISTOIRE;
						position_curseur_act = MODE_ARENE;
					}
					break;
				
				// La touche "flèche_gauche" est appuyée.
				case SDLK_LEFT:
					if(position_curseur_act == MODE_ARENE)
					{
						position_curseur_prec = MODE_ARENE;
						position_curseur_act = MODE_HISTOIRE;
					}
					break;
				
				// La touche "flèche_bas" est appuyée.
				case SDLK_DOWN:
					if(position_curseur_act == MODE_ARENE || position_curseur_act == MODE_HISTOIRE)
					{
						position_curseur_prec = position_curseur_act;
						position_curseur_act = RETOUR_MENU;
					}
					break;
				
				// La touche "flèche_haut" est appuyée.
				case SDLK_UP:
					if(position_curseur_act == RETOUR_MENU)
					{
						position_curseur_act = position_curseur_prec;
						position_curseur_prec = RETOUR_MENU;
					}
					break;
				
				// La touche "retour" est appuyée.
				case SDLK_RETURN:
					switch(position_curseur_act)
					{
					// Si l'utilisateur choisi de retourner au menu principal.
					case RETOUR_MENU:
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
	
	
	libererTexturesEcran();
}

void Jeu::chargerTexturesEcran()
{
	char chemin_image_cadre_selection[] = "img/jeu/jeu_cadre_selection.bmp";
	char chemin_image_fond_jeu[] = "img/jeu/jeu_image_fond.bmp";
	char chemin_image_mode_arene[] = "img/jeu/jeu_mode_arene.bmp";
	char chemin_image_mode_histoire[] = "img/jeu/jeu_mode_histoire.bmp";
	char chemin_image_retour_menu[] = "img/jeu/jeu_retour_menu_principal.bmp";
	
	m_texture_cadre_selection = new Texture(chemin_image_cadre_selection);
	m_texture_fond_jeu = new Texture(chemin_image_fond_jeu);
	m_texture_mode_arene = new Texture(chemin_image_mode_arene);
	m_texture_mode_histoire = new Texture(chemin_image_mode_histoire);
	m_texture_retour_menu = new Texture(chemin_image_retour_menu);
}

void Jeu::libererTexturesEcran()
{
	delete m_texture_cadre_selection;
	delete m_texture_fond_jeu;
	delete m_texture_mode_arene;
	delete m_texture_mode_histoire;
	delete m_texture_retour_menu;
	
	m_texture_cadre_selection = NULL;
	m_texture_fond_jeu = NULL;
	m_texture_mode_arene = NULL;
	m_texture_mode_histoire = NULL;
	m_texture_retour_menu = NULL;
}