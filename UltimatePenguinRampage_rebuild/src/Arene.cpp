#include <iostream>

#include "Arene.h"
#include "UPR.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.*/
Arene::Arene()
{
	// Initialisation des attributs à des valeurs par défaut.
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.w = UPR::LARGEUR_ECRAN;
	m_camera.h = UPR::HAUTEUR_ECRAN;
	m_est_prete = false;
	m_ticks_image = 0;
}
//---------------------------------

// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Arene::~Arene()
{
	// Aucun attribut à détruire.
}
//---------------------------------

// Fonctions membres publiques
//---------------------------------
/* Charge les éléments requis pour le fonctionnement de cette instance d'Arene.*/
void Arene::charger()
{
	// Chargement de la carte et gestion d'un échec potentiel.
	// temp
	std::cout << "Chargement de la Carte..." << std::endl;
	if(!m_carte.charger("rsc/map/carte_test_1.txt"))
	{
		// temp
		std::cout << "Chargement de l'arene interrompu : le chargement de la carte a echoue." << std::endl;
		
		m_est_prete = false;
		return;
	}
	// temp
	std::cout << "Carte chargee avec succes." << std::endl;
	
	// temp
	std::cout << "Chargement de l'arene termine." << std::endl;
	
	// Indication que l'arène est prête à être lancée.
	m_est_prete = true;
}

/* Lance l'arène si elle a été précédemment préparée à l'aide de #charger().*/
void Arene::lancer()
{
	// Vérification si l'arène est prête à être lancée.
	if(!m_est_prete)
	{
		/** \todo Affichage d'un message d'erreur graphique si on tente le lancement d'une instance d'Arene qui n'est pas prête.*/
		// temp
		std::cout << "Erreur : tentative de lancement d'une arène incorrectement preparee." << std::endl;
		return;
	}
	
	// Objet pour la manipulation des événements.
	SDL_Event e;
	
	// Contrôle de la boucle de l'arène.
	bool quit = false;
	
	//---------------------------------
	// Démarrage de l'arène
	
	// temp
	std::cout << "Lancement de l'arene..." << std::endl;
	
	// Boucle de l'arène
	while(!quit)
	{
		// Début du chronométrage de l'image.
		m_timer.start();
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		m_carte.render(m_camera);
		
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
				// temp
				// La touche "q" est appuyée.
				case SDLK_q:
					// Changement de la position du curseur.
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
}

/* Réinitialise une arène lancée et terminée.*/
void Arene::reinitialiser()
{
	// Réinitialisation de la carte.
	m_carte.reinitialiser();
	
	// Réinitialisation des attributs à des valeurs par défaut.
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.w = UPR::LARGEUR_ECRAN;
	m_camera.h = UPR::HAUTEUR_ECRAN;
	m_ticks_image = 0;
	
	// temp
	std::cout << "Arene reinitialisee." << std::endl;
	
	// Indication que l'arène n'est plus prête à être lancée.
	m_est_prete = false;
}
//---------------------------------