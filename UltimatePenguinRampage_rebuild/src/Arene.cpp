#include <fstream>
#include <iostream>

#include "Arene.h"
#include "UPR.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Arene::Arene() : m_est_prete(false), m_joueur(NULL), m_ticks_image(0)
{
	// Initialisation des attributs à des valeurs par défaut.
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.w = UPR::LARGEUR_ECRAN;
	m_camera.h = UPR::HAUTEUR_ECRAN;
}
//-------------------------------------

// Destructeur
//-------------------------------------
/* Destructeur par défaut.*/
Arene::~Arene()
{
	// Aucun attribut à détruire.
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Charge les éléments requis pour le fonctionnement de cette instance d'Arene.*/
void Arene::charger(std::string const &chemin_fichier)
{
	// Le chemin d'accès à la carte de l'arène.
	std::string chemin_carte = "";
	
	// Chargement du fichier donné dans un flux d'entrée.
	std::ifstream fichier(chemin_fichier.c_str());
	
	// La ligne de lecture du fichier.
	std::string ligne = "";
	
	//---------------------------------
	// Démarrage du chargement de l'arène.
	
	// Gestion d'un échec potentiel du chargement du fichier.
	if(!fichier.is_open())
	{
		// Affichage d'un message d'erreur.
		std::cout << "Erreur : impossible de charger l'arene depuis le fichier " << chemin_fichier << std::endl;
		
		m_est_prete = false;
	}
	else
	{
		// temp
		std::cout << "Lecture du fichier " << chemin_fichier << std::endl;
		
		//-----------------------------
		// Lecture des [infos_arene]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[infos_arene]")
		{
			std::cout << "Erreur : [infos_arene] manquant dans : " << chemin_fichier << std::endl;
			
			m_est_prete = false;
			goto fin;
		}
		
		// Lecture du chemin de la carte.
		fichier >> ligne; fichier >> ligne;
		chemin_carte = ligne;
	
		//---------------------------------
		// Chargement de la carte.
		
		// temp
		std::cout << "Chargement de la Carte..." << std::endl;
		
		// Gestion d'un échec du chargement de la carte.
		if(!m_carte.charger(chemin_carte))
		{
			// temp
			std::cout << "Chargement de l'arene interrompu : le chargement de la carte a echoue." << std::endl;
			
			m_est_prete = false;
			goto fin;
		}
		
		// temp
		std::cout << "Carte chargee avec succes." << std::endl;
		
		//---------------------------------
		// Chargement du joueur.
		
		m_joueur = new Joueur(m_carte.getPositionDepartJoueur());
		
		//---------------------------------
		// Fin du chargement.
		
		// temp
		std::cout << "Chargement de l'arene termine." << std::endl;
		
		// Indication que l'arène est prête à être lancée.
		m_est_prete = true;
		
		// Fermeture du fichier.
		fin:
		fichier.close();
	}
}

/* Lance l'arène si elle a été précédemment préparée à l'aide de #charger().*/
void Arene::lancer()
{
	// Vérification si l'arène est prête à être lancée.
	if(!m_est_prete)
	{
		/** \todo Affichage d'un message d'erreur graphique si on tente le lancement d'une instance d'Arene qui n'est pas prête.*/
		// temp
		std::cout << "Erreur : tentative de lancement d'une arene incorrectement preparee." << std::endl;
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
		
		//-----------------------------
		// Mise-à-jour des éléments.
		
		m_joueur->update(m_carte);
		updateCamera();
		
		//-----------------------------
		// Affichage des images
		
		// Nettoyage du renderer.
		SDL_RenderClear(UPR::renderer_SDL);
		
		m_carte.render(m_camera);
		m_joueur->render(m_camera);
		
		// Affichage à l'écran.
		SDL_RenderPresent(UPR::renderer_SDL);
		
		//-----------------------------
		// Gestion des événements.
		while(SDL_PollEvent(&e) != 0)
		{
			// On donne l'événement au joueur.
			m_joueur->gererEvenement(e, m_camera);
			
			// Si une touche est appuyée.
			if(e.type == SDL_KEYDOWN)
			{
				// Switch sur le symbole de la touche appuyée.
				switch(e.key.keysym.sym)
				{
				// La touche "echap" est appuyée.
				case SDLK_ESCAPE:
					// Quitte l'arène sans confirmation.
					quit = true;
					break;
				}
			}
		}
		
		//-----------------------------
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
	
	// Destruction du joueur.
	delete m_joueur;
	m_joueur = NULL;
	
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
//-------------------------------------

// Fonctions membres privées
//-------------------------------------
/* Met à jour la position de la caméra.*/
void Arene::updateCamera()
{
	m_camera.x = m_joueur->getPosition().x + ((m_joueur->getLargeurImage() - m_camera.w) / 2);
	m_camera.y = m_joueur->getPosition().y + ((m_joueur->getHauteurImage() - m_camera.h) / 2);
}
//-------------------------------------