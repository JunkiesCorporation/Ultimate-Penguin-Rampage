#include <iostream>

#include "Joueur.h"
#include "Jeu.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.
 *
 * Appel explicitement le constructeur par défaut d'Entité.
 */
Joueur::Joueur() : super(), m_armes_portees(0), m_arme_selectionnee(NULL), m_compteur_recharge(0), m_num_arme_selectionnee(0), m_points_de_vie(0)
{
	// Initialisation des attributs.
	for(int i = 0; i < NB_ACTIONS; i++)
	{
		m_actions[i] = false;
	}
	for(int i = 0; i < NB_DIRECTIONS; i++)
	{
		m_textures[i] = NULL;
	}
	
	// temp
	std::cout << "Joueur cree." << std::endl;
}

/* Constructeur de chargement.*/
Joueur::Joueur(std::vector<int> const &id_armes_depart, Coordonnees pos_depart) : super(pos_depart), m_compteur_recharge(0), m_points_de_vie(100)
{
	// Initialisation des attributs.
	// Attributs hérités.
	m_vitesse_max = 4;
	// Attributs privés.
	for(int i = 0; i < NB_ACTIONS; i++)
	{
		m_actions[i] = false;
	}
	
	// Chargement des images du joueur.
	m_textures[HAUT] = new Texture("rsc/img/jeu/entites/joueur/joueur_haut.bmp");
	m_textures[HAUT_DROITE] = new Texture("rsc/img/jeu/entites/joueur/joueur_haut_droite.bmp");
	m_textures[DROITE] = new Texture("rsc/img/jeu/entites/joueur/joueur_droite.bmp");
	m_textures[BAS_DROITE] = new Texture("rsc/img/jeu/entites/joueur/joueur_bas_droite.bmp");
	m_textures[BAS] = new Texture("rsc/img/jeu/entites/joueur/joueur_bas.bmp");
	m_textures[BAS_GAUCHE] = new Texture("rsc/img/jeu/entites/joueur/joueur_bas_gauche.bmp");
	m_textures[GAUCHE] = new Texture("rsc/img/jeu/entites/joueur/joueur_gauche.bmp");
	m_textures[HAUT_GAUCHE] = new Texture("rsc/img/jeu/entites/joueur/joueur_haut_gauche.bmp");
	
	// Attribution de l'image de départ par défaut.
	m_image = m_textures[BAS];
	
	// Récupération des armes correspondants aux id donnés.
	for(std::vector<int>::const_iterator it = id_armes_depart.cbegin(); it != id_armes_depart.cend(); ++it)
	{
		m_armes_portees.emplace_back(Jeu::getArmeDepuisID(*it));
	}
	
	// Sélection automatique de la première arme portée.
	m_num_arme_selectionnee = 0;
	m_arme_selectionnee = &m_armes_portees.at(m_num_arme_selectionnee);
}
//---------------------------------


// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Joueur::~Joueur()
{
	for(int i = 0; i < NB_DIRECTIONS; i++)
	{
		delete m_textures[i];
		m_textures[i] = NULL;
	}
	
	m_arme_selectionnee = NULL;
	m_armes_portees.clear();
	
	// temp
	std::cout << "Joueur detruit." << std::endl;
}
//---------------------------------


// Fonctions membres publiques
//---------------------------------
/* Gère les événements s'ils s'appliquent au Joueur.*/
void Joueur::gererEvenement(SDL_Event const &e, SDL_Rect const &camera)
{
	// Si l'utilisateur a déplacé la souris.
	if(e.type == SDL_MOUSEMOTION)
	{
		// Il y a eu un changement de direction.
		m_actions[CHANGE_DIRECTION] = true;
		
		// La position du centre de l'image du joueur.
		Coordonnees pos_centre_camera = { camera.w / 2, camera.h / 2};
		
		// Récupération des nouvelles coordonnées de la souris et calcul de sa position relative au joueur.
		Coordonnees pos_souris_relative = { e.motion.x - pos_centre_camera.x, e.motion.y - pos_centre_camera.y};
		
		// Calcul de la direction en fonction du cadran dans lequel la souris est.
		if(pos_souris_relative.x >= 0 && pos_souris_relative.y < 0)
		{
			m_angle_visee = atan(((double)pos_souris_relative.x) / ((-1.)*(double)pos_souris_relative.y));
		}
		else if(pos_souris_relative.x > 0 && pos_souris_relative.y >= 0)
		{
			m_angle_visee = M_PI_2 + atan(((double)pos_souris_relative.y) / ((double)pos_souris_relative.x));
		}
		else if(pos_souris_relative.x <= 0 && pos_souris_relative.y > 0)
		{
			m_angle_visee = M_PI + atan(((-1.)*(double)pos_souris_relative.x)/((double)pos_souris_relative.y));
		}
		else if(pos_souris_relative.x < 0 && pos_souris_relative.y <= 0)
		{
			m_angle_visee = M_PI + M_PI_2 + atan(((-1.)*(double)pos_souris_relative.y) / ((-1.)*(double)pos_souris_relative.x));
		}
	}
	// Si l'utilisateur appuie sur une touche.
	else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
		// Si l'utilisateur appuie sur "d".
		case SDLK_d:
			m_actions[DIR_DROITE] = true;
			break;
			
		// Si l'utilisateur appuie sur "echap"
		case SDLK_ESCAPE:
			m_image = NULL;
			break;
			
		// Si l'utilisateur appuie sur "q".
		case SDLK_q:
			m_actions[DIR_GAUCHE] = true;
			break;
			
		// Si l'utilisateur appuie sur "s".
		case SDLK_s:
			m_actions[DIR_BAS] = true;
			break;
			
		// Si l'utilisateur appuie sur "z".
		case SDLK_z:
			m_actions[DIR_HAUT] = true;
			break;
		}
	}
	// Si l'utilisateur relâche une touche
	else if(e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
		// Si l'utilisateur relâche "d".
		case SDLK_d:
			m_actions[DIR_DROITE] = false;
			break;
		
		// Si l'utilisateur relâche "q".
		case SDLK_q:
			m_actions[DIR_GAUCHE] = false;
			break;
			
		// Si l'utilisateur relâche "s".
		case SDLK_s:
			m_actions[DIR_BAS] = false;
			break;
			
		// Si l'utilisateur relâche "z".	
		case SDLK_z:
			m_actions[DIR_HAUT] = false;
			break;
		}
	}
	// Si l'utilisateur appuie sur un bouton de la souris.
	else if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		// Si l'utilisateur fait un click gauche.
		if(e.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "tps recharge : " << m_arme_selectionnee->getTpsRecharge() << std::endl;
			m_actions[UTILISE_ARME] = true;
		}
	}
}

/* Inflige les dégâts indiqués au joueur.*/
void Joueur::infligerDegats(int degats)
{
	m_points_de_vie -= degats;
}

/* Met à jour le joueur.*/
void Joueur::update(Carte const &carte)
{
	//---------------------------------
	// Mise à jour des attributs du joueur.
	
	//---------------------------------
	// Déplacement du joueur.

	// Si le joueur demande à se déplacer.
	if(m_actions[DIR_BAS] || m_actions[DIR_DROITE] || m_actions[DIR_GAUCHE] || m_actions[DIR_HAUT])
	{
		// Attribution de l'angle de déplacement en fonction du déplacement demandé.
		if(m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = 0;
		}
		else if(m_actions[DIR_HAUT] && m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = M_PI_4;
		}
		else if(!m_actions[DIR_HAUT] && m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = M_PI_2;
		}
		else if(!m_actions[DIR_HAUT] && m_actions[DIR_DROITE] && m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = 3. * M_PI_4;
		}
		else if(!m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = M_PI;
		}
		else if(!m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && m_actions[DIR_BAS] && m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = 5. * M_PI_4;
		}
		else if(!m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = 3. * M_PI_2;
		}
		else if(m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && m_actions[DIR_GAUCHE])
		{
			m_angle_deplacement = 7. * M_PI_4;
		}
		
		// Indication que cette entité se déplace.
		m_se_deplace = true;
	}
	else
	{
		m_se_deplace = false;
	}
	
	// Appel à Entite::update().
	super::update(carte);
	
	// Changement de l'image du joueur en fonction de la direction.
	if(m_actions[CHANGE_DIRECTION])
	{
		if(m_angle_visee >= 15. * M_PI_8 || m_angle_visee < M_PI_8)
		{
			m_image = m_textures[HAUT];
		}
		else if(m_angle_visee >= M_PI_8 && m_angle_visee < 3. * M_PI_8)
		{
			m_image = m_textures[HAUT_DROITE];
		}
		else if(m_angle_visee >= 3. * M_PI_8 && m_angle_visee < 5. * M_PI_8)
		{
			m_image = m_textures[DROITE];
		}
		else if(m_angle_visee >= 5. * M_PI_8 && m_angle_visee < 7. * M_PI_8)
		{
			m_image = m_textures[BAS_DROITE];
		}
		else if(m_angle_visee >= 7. * M_PI_8 && m_angle_visee < 9. * M_PI_8)
		{
			m_image = m_textures[BAS];
		}
		else if(m_angle_visee >= 9. * M_PI_8 && m_angle_visee < 11. * M_PI_8)
		{
			m_image = m_textures[BAS_GAUCHE];
		}
		else if(m_angle_visee >= 11. * M_PI_8 && m_angle_visee < 13. * M_PI_8)
		{
			m_image = m_textures[GAUCHE];
		}
		else if(m_angle_visee >= 13. * M_PI_8 && m_angle_visee < 15. * M_PI_8)
		{
			m_image = m_textures[HAUT_GAUCHE];
		}
		
		m_actions[CHANGE_DIRECTION] = false;
	}
	
	//---------------------------------
	// Utilisation de l'arme.
	
	// Écoulement du compteur de recharge.
	if(m_compteur_recharge > 0)
	{
		m_compteur_recharge--;
		std::cout << "compteur recharge : " << m_compteur_recharge << std::endl;
	}
	
	if(m_actions[UTILISE_ARME] && m_compteur_recharge == 0)
	{
		m_compteur_recharge = m_arme_selectionnee->getTpsRecharge();
		m_arme_selectionnee->utiliser(*this);
		m_actions[UTILISE_ARME] = false;
	}
}
//---------------------------------