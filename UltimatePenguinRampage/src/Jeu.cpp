#include <string>
#include <fstream>
#include <iostream>

#include "Jeu.h"
#include "Struct.h"
#include "UPR.h"


// Initialisation de la liste des exemplaires d'armes.
std::vector<Arme> Jeu::m_liste_armes(0);
// Initialisation de la liste des exemplaires des projectiles
std::vector<Projectile> Jeu::m_liste_projectiles(0);

// Initialisation de la liste des textures des projectiles.
std::vector<Texture*> Jeu::m_textures_projectiles(0);


// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Jeu::Jeu() : m_arene(), m_texture_cadre_selection(NULL), m_texture_fond_jeu(NULL), m_texture_fond_mode_histoire(NULL), m_ticks_image(0), m_timer()
{
	// Initialisation des attributs à des valeurs par défaut.
	for(int i = 0; i < NB_OPTIONS; i++)
	{
		m_textures_options_ecran_jeu[i] = NULL;
	}
}
//-------------------------------------


// Destructeur
//-------------------------------------
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
	
	// Nettoyage des listes d'exemplaires d'objets.
	m_liste_armes.clear();
	m_liste_projectiles.clear();
	
	// Nettoyage des images des projectiles.
	for(int i = 0; i < m_textures_projectiles.size(); i++)
	{
		delete m_textures_projectiles.at(i);
		m_textures_projectiles.at(i) = NULL;
	}
	m_textures_projectiles.clear();
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Affiche l'écran principal du jeu et permet la navigation vers les fonctionnalités du jeu.*/
void Jeu::lancer(Profil* profil_joueur)
{
	// Contrôle de la boucle de l'écran principal du jeu.
	bool quit = false;
	
	// Chemin d'accès à la liste des armes.
	std::string chemin_fichier_liste_armes = "rsc/obj/armes/0_liste_armes.txt";
	
	// Chemin d'accès à la liste des projectiles.
	std::string chemin_fichier_liste_projectiles = "rsc/obj/projectiles/0_liste_projectiles.txt";
	
	// Chemin d'accès à l'image du curseur de sélection.
	char chemin_image_cadre_selection[] = "rsc/img/jeu/jeu_cadre_selection.bmp";
	
	// Le flux d'entrée pour charger la liste des armes.
	std::ifstream fichier_liste_armes;
	
	// Le flux d'entrée pour charger la liste des projectiles.
	std::ifstream fichier_liste_projectiles;
	
	// La ligne de lecture des fichiers.
	std::string ligne = "";
	
	// Le nombre d'armes à charger.
	int nombre_armes = 0;
	
	// Le nombre de projectiles à charger.
	int nombre_projectiles = 0;
	
	// La position actuelle du curseur.
	EnumOptionsEcranPrincipal position_curseur_act = MODE_HISTOIRE;
	
	// La position précédente du curseur.
	EnumOptionsEcranPrincipal position_curseur_prec = MODE_HISTOIRE;
	
	// Coordonnees des images de l'écran principal du jeu.
	Coordonnees positions_textures_ecran[NB_OPTIONS] = {{0, 0}};
	
	// Coordonnees du curseur lors de l'écran principal du jeu.
	Coordonnees positions_curseur_ecran[NB_OPTIONS] = {{0, 0}};
	
	// Chemin d'accès temporaire à l'image du projectile pendant le chargement.
	std::string temp_chemin_image_projectile = "";
	
	// ID temporaire de l'arme pendant le chargement.
	int temp_id_arme = 0;
	
	// ID temporaire du projectile pendant le chargement.
	int temp_id_projectile = 0;
	
	// Nom temporaire de l'arme pendant le chargement.
	std::string temp_nom_arme = "";
	
	// Nom temporaire du projectile pendant le chargement.
	std::string temp_nom_projectile = "";
	
	//---------------------------------
	// Démarrage du Jeu.
	
	//---------------------------------
	// Chargement des images.
	
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
	
	//---------------------------------
	// Chargement de la liste des armes.
	
	// Ouverture du fichier contenant la liste des armes.
	fichier_liste_armes.open(chemin_fichier_liste_armes);
	
	// Gestion d'un échec potentiel.
	if(!fichier_liste_armes.is_open())
	{
		// Affichage d'un message d'erreur.
		std::cout << "Erreur : impossible d'ouvrir le fichier " << chemin_fichier_liste_armes << std::endl;
		
		// On empêche le démarrage du jeu.
		quit = true;
	}
	else
	{
		//-----------------------------
		// Lecture des [infos_liste_armes]
		
		// Gestion d'un échec potentiel.
		fichier_liste_armes >> ligne;
		if(ligne != "[infos_liste_armes]")
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : [infos_liste_armes] manquant dans le fichier " << chemin_fichier_liste_armes << std::endl;
			
			// On empêche le démarrage du jeu et on arrête le chargement.
			quit = true;
			goto close_liste_armes;
		}
		
		// Lecture du nombre d'armes dans la liste
		fichier_liste_armes >> ligne; fichier_liste_armes >> ligne;
		nombre_armes = atoi(ligne.c_str());
		
		//-----------------------------
		// Lecture de la [liste_armes]
		
		// Gestion d'un échec potentiel.
		fichier_liste_armes >> ligne;
		if(ligne != "[liste_armes]")
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : [liste_arme] manquant dans le fichier " << chemin_fichier_liste_armes << std::endl;
			
			// On empêche le démarrage du jeu et on arrête le chargement.
			quit = true;
			goto close_liste_armes;
		}
		
		// Récupération des id et nom_fichier des armes et ajout de l'arme au vecteur.
		for(int i = 0; i < nombre_armes; i++)
		{
			// Lecture de l'id de l'arme.
			fichier_liste_armes >> ligne;
			temp_id_arme = atoi(ligne.c_str());
			
			// Lecture du nom du fichier de l'arme.
			fichier_liste_armes >> ligne;
			temp_nom_arme = ligne;
			
			// Création d'une nouvelle instance de Arme et ajout à la liste.
			m_liste_armes.emplace_back(temp_id_arme, temp_nom_arme);
		}
		
		close_liste_armes:
		fichier_liste_armes.close();
	}
	
	//---------------------------------
	// Chargement de la liste des projectiles.
	
	// Ouverture du fichier contenant la liste des projectiles.
	fichier_liste_projectiles.open(chemin_fichier_liste_projectiles);
	
	// Gestion d'un échec potentiel.
	if(!fichier_liste_projectiles.is_open())
	{
		// Affichage d'un message d'erreur.
		std::cout << "Erreur : impossible d'ouvrir le fichier " << chemin_fichier_liste_projectiles << std::endl;
		
		// On empêche le démarrage du jeu.
		quit = true;
	}
	else
	{
		//-----------------------------
		// Lecture des [infos_liste_projectiles]
		
		fichier_liste_projectiles >> ligne;
		if(ligne != "[infos_liste_projectiles]")
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : [infos_liste_projectiles] manquant dans le fichier " << chemin_fichier_liste_projectiles << std::endl;
			
			// On empêche le démarrage du jeu et on arrête le chargement.
			quit = true;
			goto close_liste_projectiles;
		}
		
		// Lecture du nombre de projectiles dans la liste
		fichier_liste_projectiles >> ligne; fichier_liste_projectiles >> ligne;
		nombre_projectiles = atoi(ligne.c_str());
		
		//-----------------------------
		// Lecture de la [liste_projectiles]
		
		// Gestion d'un échec potentiel.
		fichier_liste_projectiles >> ligne;
		if(ligne != "[liste_projectiles]")
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : [liste_projectiles] manquant dans le fichier " << chemin_fichier_liste_projectiles << std::endl;
			
			// On empêche le démarrage du jeu et on arrête le chargement.
			quit = true;
			goto close_liste_projectiles;
		}
		
		// Récupération des id et nom_fichier des projectiles et ajout du projectile au vecteur. Récupération du chemin d'image du projectile et ajout au vecteur de textures.
		for(int i = 0; i < nombre_projectiles; i++)
		{
			// Lecture de l'id du projectile.
			fichier_liste_projectiles >> ligne;
			temp_id_projectile = atoi(ligne.c_str());
			
			// Lecture du nom du fichier du projectile.
			fichier_liste_projectiles >> ligne;
			temp_nom_projectile = ligne;
			
			// Lecture du chemin d'image du projectile.
			fichier_liste_projectiles >> ligne;
			temp_chemin_image_projectile = ligne;
			
			// Ajout de l'image du projectile au vecteur.
			m_textures_projectiles.emplace_back(new Texture(ligne.c_str()));
			
			// Création d'une nouvelle instance de Projectile et ajout à la liste.
			m_liste_projectiles.emplace_back(temp_id_projectile, temp_nom_projectile);
		}
		
		close_liste_projectiles:
		fichier_liste_projectiles.close();
	}
	
	//---------------------------------
	// Boucle de l'écran principal du jeu.
	while(!quit)
	{
		// Début du chronométrage de l'image.
		m_timer.start();
		
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
				case SDLK_d:
					// Changement de la position du curseur.
					if(position_curseur_act == MODE_HISTOIRE)
					{
						position_curseur_prec = MODE_HISTOIRE;
						position_curseur_act = MODE_ARENE;
					}
					break;
				
				// La touche "flèche_gauche" est appuyée.
				case SDLK_q:
					// Changement de la position du curseur.
					if(position_curseur_act == MODE_ARENE)
					{
						position_curseur_prec = MODE_ARENE;
						position_curseur_act = MODE_HISTOIRE;
					}
					break;
				
				// La touche "flèche_bas" est appuyée.
				case SDLK_s:
					// Changement de la position du curseur.
					if(position_curseur_act == MODE_ARENE || position_curseur_act == MODE_HISTOIRE)
					{
						position_curseur_prec = position_curseur_act;
						position_curseur_act = RETOUR_MENU;
					}
					break;
				
				// La touche "flèche_haut" est appuyée.
				case SDLK_z:
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
		m_ticks_image = m_timer.getTicks();
		if(m_ticks_image < UPR::TICKS_ECRAN_PAR_IMAGE)
		{
			SDL_Delay(UPR::TICKS_ECRAN_PAR_IMAGE - m_ticks_image);
		}
	}
	
	//---------------------------------
	// Fermeture du Jeu une fois terminé.
	
	// Suppression de la texture du cadre de sélection.
	delete m_texture_cadre_selection;
	m_texture_cadre_selection = NULL;
	
	// Libération des images de l'écran principal du jeu.
	libererTexturesEcran();
	
	// Effacement de la liste d'armes.
	m_liste_armes.clear();
	
	// Effacement de la liste de projectiles.
	m_liste_projectiles.clear();
}
//-------------------------------------


// Fonctions membres publiques et statiques
//-------------------------------------
/* Retourne l'arme dont l'id correspond à celui donné en paramètre.*/
Arme Jeu::getArmeDepuisID(int const &p_id)
{
	// Arme temporaire à retourner.
	Arme temp_arme;
	
	// Recherche de l'arme demandée.
	for(int i = 0; i < m_liste_armes.size(); i++)
	{
		if(m_liste_armes.at(i).getID() == p_id)
		{
			temp_arme = m_liste_armes.at(i);
			break;
		}
	}
	
	return temp_arme;
}

/* Retourne le projectile dont l'id correspond à celui donné en paramètre.*/
Projectile Jeu::getProjectileDepuisID(int const &p_id)
{
	// Arme temporaire à retourner.
	Projectile temp_projectile;
	
	// Recherche de l'arme demandée.
	for(int i = 0; i < m_liste_projectiles.size(); i++)
	{
		if(m_liste_projectiles.at(i).getID() == p_id)
		{
			temp_projectile = m_liste_projectiles.at(i);
			break;
		}
	}
	
	return temp_projectile;
}

/* Retourne l'image correspondant à l'id du projectile donné.*/
Texture* Jeu::getTextureProjectileDepuisID(int const &p_id)
{
	// L'indice de la Texture à retourner.
	int temp_indice = -1;
	
	// Récupération de l'indice grâce à l'id donné.
	for(int i = 0; i < m_liste_projectiles.size(); i++)
	{
		if(m_liste_projectiles.at(i).getID() == p_id)
		{
			temp_indice = i;
			break;
		}
	}
	
	// Retour de la texture demandée, sauf erreur.
	if(temp_indice != -1 && temp_indice < m_textures_projectiles.size())
	{
		return m_textures_projectiles.at(temp_indice);
	}
	else
	{
		std::cout << "Erreur : Aucune Texture trouvee correspondant a l'id " << p_id << std::endl;
		return NULL;
	}
}
//-------------------------------------


// Fonctions membres privées
//-------------------------------------
/* Charge les textures nécessaires à l'écran principal du jeu.*/
void Jeu::chargerTexturesEcran()
{
	// Chemins des images à charger.
	char chemin_image_fond_jeu[] = "rsc/img/jeu/jeu_image_fond.bmp";
	std::string chemin_images_ecran_jeu[NB_OPTIONS] =
	{
		"rsc/img/jeu/jeu_mode_histoire.bmp",
		"rsc/img/jeu/jeu_mode_arene.bmp",
		"rsc/img/jeu/jeu_retour_menu_principal.bmp"
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
	char chemin_image_fond_mode_histoire[] = "rsc/img/jeu/mode_histoire/mode_histoire_image_fond.bmp";
	
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
	m_ticks_image = 0;
	
	// Boucle de sélection de niveau.
	while(!quit)
	{
		// Début du chronométrage de l'image.
		m_timer.start();
		
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
					m_arene.charger("rsc/arenes/arene_1.txt");
					
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
		m_ticks_image = m_timer.getTicks();
		if(m_ticks_image < UPR::TICKS_ECRAN_PAR_IMAGE)
		{
			SDL_Delay(UPR::TICKS_ECRAN_PAR_IMAGE - m_ticks_image);
		}
	}
	
	// Libération des images du mode histoire.
	libererTexturesModeHistoire();
}
//-------------------------------------