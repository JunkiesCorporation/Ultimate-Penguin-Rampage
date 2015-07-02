#include <iostream>

#include "Texture.h"
#include "Timer.h"
#include "UPR.h"
#include "Utils.h"

SDL_Window* UPR::fenetre_SDL = NULL;
SDL_Renderer* UPR::renderer_SDL = NULL;

/** La fonction main.
 *
 * Initialise la SDL grâces aux méthodes static de la classe Utils, lance la cinématique d'introduction puis créé une instance d'UPR.
 * 
 * Une fois le jeu quitté, quitte la SDL correctement grâce à Utils::quitter().
 */
int main(int argc, char* args[])
{	
	// Initialisation de la SDL.
	if(!Utils::initialisationSDL())
	{
		std::cout << "Une erreur est survenue lors de l'initialisation de la SDL : " << std::endl;
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		std::cout << "Le programme va s'arreter." << std::endl;
		return -1;
	}
	
	// Création d'une instance du programme. Comme elle n'est pas attribuée avec new il n'y a pas de delete correspondant. L'instance est détruite à la fin de la fonction main().
	UPR instance_programme;
	
	// Déroulement du programme.
	instance_programme.lancer();
	
	// Fermeture de la SDL.
	Utils::quitterSDL();
	
	return 0;
}

/* Constructeur par défaut.*/
UPR::UPR()
{
	// temp
	std::cout << "Programme instancie" << std::endl << std::endl;
}

/* Destructeur par défaut.*/
UPR::~UPR()
{
	// temp
	std::cout << "Instance du Programme detruite" << std::endl;
}

/* Fonction responsable du programme.*/
void UPR::lancer()
{
	// Contrôle de la boucle principale du programme.
	bool quit = false;
	
	//---------------------------------
	
	// Boucle principale du programme.
	while(!quit)
	{
		// temp
		std::cout << "Affichage du menu principal" << std::endl;
		
		switch(menuPrincipal())
		{
		// Si l'utilisateur à choisi de jouer avec un nouveau profil.
		case 0:			
			// Lancement du jeu avec le profil créé.
			instance_jeu.lancer(&profil_joueur);
			
			std::cout << "Instance jeu terminee." << std::endl;
			
			// On ne quitte pas le programme à la fin du jeu, on ré-affiche le menu principal.
			break;
		
		// Si l'utilisateur à choisi de jouer avec un profil chargé.
		case 1:
			// Lancement du jeu avec le profil chargé.
			instance_jeu.lancer(&profil_joueur);
			
			// On ne quitte pas le programme à la fin du jeu, on ré-affiche le menu principal.
			break;
		
		// Si l'utilisateur à choisi de quitter le jeu.
		case 3:
			quit = true;
			break;
		}
		
		// temp
		std::cout << "Menu principal termine." << std::endl << std::endl;
	}
}

/* Gère l'affichage et le contrôle du menu principal.*/
int UPR::menuPrincipal()
{
	// Choix à retourner.
	int choix = 0;
	
	// Contrôle de la boucle du menu.
	bool quit = false;
	
	/* Liste des images du menu :
	 * - image de fond
	 * - image nouveau profil
	 * - image charger profil
	 * - image options
	 * - image quitter
	 * - image curseur de sélection
	 */
	
	// Chemins des images du menu.
	char chemin_image_fond[] = "img/menu_principal/menu_principal.bmp";
	char chemin_image_nouveau_profil[] = "img/menu_principal/nouveau_profil.bmp";
	char chemin_image_charger_profil[] = "img/menu_principal/charger_profil.bmp";
	char chemin_image_options[] = "img/menu_principal/options.bmp";
	char chemin_image_quitter[] = "img/menu_principal/quitter.bmp";
	char chemin_image_curseur[] = "img/commun/curseur.bmp";
	
	// Textures contenant les images du menu.
	Texture* texture_fond = NULL;
	Texture* texture_nouveau_profil = NULL;
	Texture* texture_charger_profil = NULL;
	Texture* texture_options = NULL;
	Texture* texture_quitter = NULL;
	Texture* texture_curseur = NULL;
	
	// Positions à l'écran des images du menu.
	int positions_fixes[4][2] = {{0}};
	
	// Positions à l'écran du curseur, une pour chaque choix.
	int positions_curseur[4][2] = {{0}};
	
	// Élément de manipulations des événements.
	SDL_Event e;
	
	// Timer pour bloquer les FPS à 60 et nombre ticks par image.
	Timer timer;
	int ticks_image = 0;
	
	//---------------------------------
	
	// temp
	std::cout << "Chargement des images du menu..." << std::endl;
	
	// Chargement des images du menu.
	texture_fond = new Texture(chemin_image_fond);
	texture_nouveau_profil = new Texture(chemin_image_nouveau_profil);
	texture_charger_profil = new Texture(chemin_image_charger_profil);
	texture_options = new Texture(chemin_image_options);
	texture_quitter = new Texture(chemin_image_quitter);
	texture_curseur = new Texture(chemin_image_curseur);
	
	// temp
	std::cout << "Chargement des images termine." << std::endl;
	
	// Calcul des positions des images du menu.
	positions_fixes[0][0] = (UPR::LARGEUR_ECRAN - texture_nouveau_profil->getLargeur()) / 2;
	positions_fixes[0][1] = 250;
	positions_fixes[1][0] = (UPR::LARGEUR_ECRAN - texture_charger_profil->getLargeur()) / 2;
	positions_fixes[1][1] = 325;
	positions_fixes[2][0] = (UPR::LARGEUR_ECRAN - texture_options->getLargeur()) / 2;
	positions_fixes[2][1] = 400;
	positions_fixes[3][0] = (UPR::LARGEUR_ECRAN - texture_quitter->getLargeur()) / 2;
	positions_fixes[3][1] = 475;
	
	// Calcul des positions du curseur.
	positions_curseur[0][0] = positions_fixes[0][0] - texture_curseur->getLargeur() - 5;
	positions_curseur[0][1] = positions_fixes[0][1];
	positions_curseur[1][0] = positions_fixes[1][0] - texture_curseur->getLargeur() - 5;
	positions_curseur[1][1] = positions_fixes[1][1];
	positions_curseur[2][0] = positions_fixes[2][0] - texture_curseur->getLargeur() - 5;
	positions_curseur[2][1] = positions_fixes[2][1];
	positions_curseur[3][0] = positions_fixes[3][0] - texture_curseur->getLargeur() - 5;
	positions_curseur[3][1] = positions_fixes[3][1];
	
	// Boucle du menu.
	while(!quit)
	{
		// Début du chronométrage de l'image.
		timer.start();
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		// Affichage des images fixes du menu.
		texture_fond->render(0, 0);
		texture_nouveau_profil->render(positions_fixes[0][0], positions_fixes[0][1]);
		texture_charger_profil->render(positions_fixes[1][0], positions_fixes[1][1]);
		texture_options->render(positions_fixes[2][0], positions_fixes[2][1]);
		texture_quitter->render(positions_fixes[3][0], positions_fixes[3][1]);
		
		// Render de l'image du curseur.
		texture_curseur->render(positions_curseur[choix % 4][0], positions_curseur[choix % 4][1]);
		
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
				// La touche "flèche_bas" est appuyée.
				case SDLK_DOWN:
					choix++;
					if(choix > 3) { choix = 0; }
					break;
				
				// La touche "flèche_haut" est appuyée.
				case SDLK_UP:
					choix--;
					if(choix < 0) { choix = 3; }
					break;
				
				// La touche "retour" est appuyée.
				case SDLK_RETURN:
					std::cout << "Choix menu selectionne : " << choix << std::endl;
					switch(choix)
					{
					// Si l'utilisateur souhaite créer un nouveau profil.
					case 0:
						// Si la création du nouveau profil a réussi.
						if(nouveauProfil())
						{
							quit = true;
						}
						break;
					
					// Si l'utilisateur souhaite charger un ancien profil.
					case 1:
						// Si le chargement de l'ancien profil a réussi.
						if(chargerProfil())
						{
							quit = true;
						}
						break;
					
					// Si l'utilisateur souhaite changer les options.
					case 2:
						// reglageOptions();
						break;
					
					// Si l'utilisateur choisi de quitter.
					case 3:
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
	
	// Libération des images du menu.
	delete texture_fond;
	delete texture_nouveau_profil;
	delete texture_charger_profil;
	delete texture_options;
	delete texture_quitter;
	delete texture_curseur;
	
	// Fermeture des pointeurs.
	texture_fond = NULL;
	texture_nouveau_profil = NULL;
	texture_charger_profil = NULL;
	texture_options = NULL;
	texture_quitter = NULL;
	texture_curseur = NULL;
	
	return choix;
}

/* Gère la création d'un nouveau profil.*/
bool UPR::nouveauProfil()
{
	profil_joueur.setEmplacementSauvegarde(0);
	
	profil_joueur.setNomProfil("Debug");
	
	profil_joueur.setSiNouveau(true);
	
	return true;
}

/* Gère le chargement d'un ancien profil.*/
bool UPR::chargerProfil()
{
	profil_joueur.setEmplacementSauvegarde(0);
	
	profil_joueur.setNomProfil("Debug");
	
	profil_joueur.setSiNouveau(true);
	
	return true;
}