#include <iostream>
#include <iterator>

#include "Joueur.h"
#include "Jeu.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.
 *
 * Appel explicitement le constructeur par défaut d'Entité.
 */
Joueur::Joueur() : super(), m_armes_portees(0), m_arme_selectionnee(NULL), m_num_arme_selectionnee(0)
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
Joueur::Joueur(std::vector<int> const &id_armes_depart, Jeu const &jeu, Coordonnees pos_depart) : super(pos_depart)
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
		m_armes_portees.emplace_back(jeu.getArmeDepuisID(*it));
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
			m_direction_visee = atan(((double)pos_souris_relative.x) / ((-1.)*(double)pos_souris_relative.y));
		}
		else if(pos_souris_relative.x > 0 && pos_souris_relative.y >= 0)
		{
			m_direction_visee = M_PI_2 + atan(((double)pos_souris_relative.y) / ((double)pos_souris_relative.x));
		}
		else if(pos_souris_relative.x <= 0 && pos_souris_relative.y > 0)
		{
			m_direction_visee = M_PI + atan(((-1.)*(double)pos_souris_relative.x)/((double)pos_souris_relative.y));
		}
		else if(pos_souris_relative.x < 0 && pos_souris_relative.y <= 0)
		{
			m_direction_visee = M_PI + M_PI_2 + atan(((-1.)*(double)pos_souris_relative.y) / ((-1.)*(double)pos_souris_relative.x));
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
}

/* Met à jour le joueur.*/
void Joueur::update(Carte const &carte)
{
	// Si les coins du personnages touchent une tile solide.
	bool coins[4];
	
	EnumDirections direction_deplacement = HAUT;
	
	// Les dimensions d'une tile de la carte.
	int hauteur_tile = carte.getHauteurTile();
	int largeur_tile = carte.getLargeurTile();
	
	// La position du joueur à l'image précédente.
	Coordonnees pos_precedente = m_position;
	
	//---------------------------------
	// Mise à jour des attributs du joueur.
	
	// Attribution de la direction en fonction du déplacement demandé.
	if(m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
	{
		direction_deplacement = HAUT;
		m_direction_deplacement = 0;
	}
	else if(m_actions[DIR_HAUT] && m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
	{
		direction_deplacement = HAUT_DROITE;
		m_direction_deplacement = M_PI_4;
	}
	else if(!m_actions[DIR_HAUT] && m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
	{
		direction_deplacement = DROITE;
		m_direction_deplacement = M_PI_2;
	}
	else if(!m_actions[DIR_HAUT] && m_actions[DIR_DROITE] && m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
	{
		direction_deplacement = BAS_DROITE;
		m_direction_deplacement = 3. * M_PI_4;
	}
	else if(!m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && m_actions[DIR_BAS] && !m_actions[DIR_GAUCHE])
	{
		direction_deplacement = BAS;
		m_direction_deplacement = M_PI;
	}
	else if(!m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && m_actions[DIR_BAS] && m_actions[DIR_GAUCHE])
	{
		direction_deplacement = BAS_GAUCHE;
		m_direction_deplacement = 5. * M_PI_4;
	}
	else if(!m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && m_actions[DIR_GAUCHE])
	{
		direction_deplacement = GAUCHE;
		m_direction_deplacement = 3. * M_PI_2;
	}
	else if(m_actions[DIR_HAUT] && !m_actions[DIR_DROITE] && !m_actions[DIR_BAS] && m_actions[DIR_GAUCHE])
	{
		direction_deplacement = HAUT_GAUCHE;
		m_direction_deplacement = 7. * M_PI_4;
	}
	
	// Si le joueur se déplace
	if(m_actions[DIR_BAS] || m_actions[DIR_DROITE] || m_actions[DIR_GAUCHE] || m_actions[DIR_HAUT])
	{
		// Calcul de la vitesse.
		m_vitesse.x = sin(m_direction_deplacement) * m_vitesse_max;
		m_vitesse.y = (-1.) * cos(m_direction_deplacement) * m_vitesse_max;
		
		// Changement de la position.
		m_position.x += m_vitesse.x;
		m_position.y += m_vitesse.y;
	}
	
	// Test de collisions avec les tiles solides de la carte et modification du déplacement si il y a collision.
    coins[0] = carte.isTileSolide(m_position.x/largeur_tile, m_position.y/hauteur_tile);
    coins[1] = carte.isTileSolide((m_position.x+largeur_tile-1)/largeur_tile, m_position.y/hauteur_tile);
    coins[2] = carte.isTileSolide((m_position.x+largeur_tile-1)/largeur_tile, (m_position.y+hauteur_tile-1)/hauteur_tile);
    coins[3] = carte.isTileSolide(m_position.x/largeur_tile, (m_position.y+hauteur_tile-1)/hauteur_tile);
    if(coins[0] && coins[1]) {
        m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
    }
    if(coins[1] && coins[2]) {
        m_position.x = (m_position.x/largeur_tile) * largeur_tile;
    }
    if(coins[2] && coins[3]) {
        m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
    }
    if(coins[3] && coins[0]) {
        m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
    }
    if (coins[0] && !(coins[1] || coins[2] || coins[3])) {
        switch(direction_deplacement) {
        case GAUCHE: m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
            break;
        case HAUT: m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
            break;
        case HAUT_DROITE: m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
            break;
        case BAS_GAUCHE: m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
            break;
        case HAUT_GAUCHE:
            if (pos_precedente.x - (m_position.x / largeur_tile + 1)*largeur_tile > pos_precedente.y - (m_position.y / hauteur_tile + 1)*hauteur_tile) {
                m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
            } else {
                m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
            }
            break;
        default:
            break;
        }
    }
    if (coins[1] && !(coins[0] || coins[2] || coins[3])) {
        switch(direction_deplacement) {
        case DROITE: m_position.x = (m_position.x/largeur_tile) * largeur_tile;
            break;
        case HAUT: m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
            break;
        case HAUT_GAUCHE: m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
            break;
        case BAS_DROITE: m_position.x = (m_position.x/largeur_tile) * largeur_tile;
            break;
        case HAUT_DROITE:
            if((m_position.x/largeur_tile)*largeur_tile - pos_precedente.x > pos_precedente.y - (m_position.y/hauteur_tile + 1) * hauteur_tile) {
                m_position.x = (m_position.x/largeur_tile) * largeur_tile;
            } else {
                m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
            }
            break;
        default:
            break;
        }
    }
    if (coins[2] && !(coins[0] || coins[1] || coins[3])) {
        switch(direction_deplacement) {
        case DROITE: m_position.x = (m_position.x/largeur_tile) * largeur_tile;
            break;
        case BAS: m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
            break;
        case BAS_GAUCHE: m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
            break;
        case HAUT_DROITE: m_position.x = (m_position.x/largeur_tile) * largeur_tile;
            break;
        case BAS_DROITE:
            if((m_position.x/largeur_tile)*largeur_tile - pos_precedente.x > (m_position.y/hauteur_tile)*hauteur_tile - pos_precedente.y) {
                m_position.x = (m_position.x/largeur_tile) * largeur_tile;
            } else {
                m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
            }
            break;
        default:
            break;
        }
    }
    if (coins[3] && !(coins[0] || coins[1] || coins[2])) {
        switch(direction_deplacement) {
        case GAUCHE: m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
            break;
        case BAS: m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
            break;
        case BAS_DROITE: m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
            break;
        case HAUT_GAUCHE: m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
            break;
        case BAS_GAUCHE:
            if(pos_precedente.x - (m_position.x/largeur_tile + 1)*largeur_tile > (m_position.y/hauteur_tile)*hauteur_tile - pos_precedente.y) {
                m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
            } else {
                m_position.y = (m_position.y/hauteur_tile) * hauteur_tile;
            }
            break;
        default:
            break;
        }
    }
	
	// Changement de l'image du joueur en fonction de la direction.
	if(m_actions[CHANGE_DIRECTION])
	{
		if(m_direction_visee >= 15. * M_PI_8 || m_direction_visee < M_PI_8)
		{
			m_image = m_textures[HAUT];
		}
		else if(m_direction_visee >= M_PI_8 && m_direction_visee < 3. * M_PI_8)
		{
			m_image = m_textures[HAUT_DROITE];
		}
		else if(m_direction_visee >= 3. * M_PI_8 && m_direction_visee < 5. * M_PI_8)
		{
			m_image = m_textures[DROITE];
		}
		else if(m_direction_visee >= 5. * M_PI_8 && m_direction_visee < 7. * M_PI_8)
		{
			m_image = m_textures[BAS_DROITE];
		}
		else if(m_direction_visee >= 7. * M_PI_8 && m_direction_visee < 9. * M_PI_8)
		{
			m_image = m_textures[BAS];
		}
		else if(m_direction_visee >= 9. * M_PI_8 && m_direction_visee < 11. * M_PI_8)
		{
			m_image = m_textures[BAS_GAUCHE];
		}
		else if(m_direction_visee >= 11. * M_PI_8 && m_direction_visee < 13. * M_PI_8)
		{
			m_image = m_textures[GAUCHE];
		}
		else if(m_direction_visee >= 13. * M_PI_8 && m_direction_visee < 15. * M_PI_8)
		{
			m_image = m_textures[HAUT_GAUCHE];
		}
		
		m_actions[CHANGE_DIRECTION] = false;
	}
}
//---------------------------------