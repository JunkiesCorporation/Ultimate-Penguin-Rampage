#include "Entite.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.*/
Entite::Entite() : m_angle_deplacement(M_PI), m_angle_visee(M_PI), m_image(NULL), m_se_deplace(false), m_vitesse_max(0)
{
	// Initialisation des attributs à des valeurs par défaut.
	m_position.x = 0;
	m_position.y = 0;
	m_vitesse.x = 0;
	m_vitesse.y = 0;
}

/* Constructeur avec position.*/
Entite::Entite(Coordonnees pos_depart) : m_angle_deplacement(M_PI), m_angle_visee(M_PI), m_image(NULL), m_se_deplace(false), m_vitesse_max(0)
{
	// Initialisation des attributs
	m_position.x = pos_depart.x;
	m_position.y = pos_depart.y;
	m_vitesse.x = 0;
	m_vitesse.y = 0;
}

/* Constructeur de copie.*/
Entite::Entite(Entite const &entite) : m_angle_deplacement(entite.getDirectionDeplacement()), m_angle_visee(entite.getDirectionVisee()), m_image(entite.getImage()), m_position(entite.getPosition()), m_se_deplace(entite.seDeplace()), m_vitesse(entite.getVitesse()), m_vitesse_max(entite.getVitesseMax())
{
	// Aucun attributs à initialiser
}
//---------------------------------

// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Entite::~Entite()
{
	// Destruction des attributs non-nuls.
	delete m_image;
	
	// Suppression des pointeurs.
	m_image = NULL;
}
//---------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Affiche l'image de l'entité si elle est sous la caméra.*/
void Entite::render(SDL_Rect const &camera)
{
	// Gestion d'une éventuelle image non chargée.
	if(m_image != NULL)
	{
		// Récupération des dimensions de l'image.
		int largeur_image = m_image->getLargeur();
		int hauteur_image = m_image->getHauteur();
		
		// Tests pour savoir si l'entité se trouve sous la camera.
		if(m_position.x + largeur_image > camera.x && m_position.x < camera.x + camera.w && m_position.y + hauteur_image > camera.y && m_position.y < camera.y + camera.h)
		{
			// Affichage de l'entité.
			m_image->render(m_position.x - camera.x, m_position.y - camera.y);
		}
	}
}

/* Met à jour l'entité.*/
void Entite::update(Carte const &carte)
{
	// Si les coins du personnages touchent une tile solide.
	bool coins[4];
	
	EnumDirections direction_deplacement;
	
	// Les dimensions d'une tile de la carte.
	int hauteur_tile = carte.getHauteurTile();
	int largeur_tile = carte.getLargeurTile();
	
	// Les dimensions de l'image de l'entité.
	int hauteur_entite = m_image->getHauteur();
	int largeur_entite = m_image->getLargeur();
	
	// La position du joueur à l'image précédente.
	Coordonnees pos_precedente = m_position;
	
	// Si l'entité est en mouvement.
	if(m_se_deplace)
	{
		// Calcul de la vitesse.
		m_vitesse.x = sin(m_angle_deplacement) * m_vitesse_max;
		m_vitesse.y = (-1.) * cos(m_angle_deplacement) * m_vitesse_max;
		
		// Changement de la position.
		m_position.x += m_vitesse.x;
		m_position.y += m_vitesse.y;
		
		// Calcul de la direction de déplacement en fonction de l'angle.
		if(m_angle_deplacement >= 15. * M_PI_8 || m_angle_deplacement < M_PI_8)
		{
			direction_deplacement = HAUT;
		}
		else if(m_angle_deplacement >= M_PI_8 && m_angle_deplacement < 3. * M_PI_8)
		{
			direction_deplacement = HAUT_DROITE;
		}
		else if(m_angle_deplacement >= 3. * M_PI_8 && m_angle_deplacement < 5. * M_PI_8)
		{
			direction_deplacement = DROITE;
		}
		else if(m_angle_deplacement >= 5. * M_PI_8 && m_angle_deplacement < 7. * M_PI_8)
		{
			direction_deplacement = BAS_DROITE;
		}
		else if(m_angle_deplacement >= 7. * M_PI_8 && m_angle_deplacement < 9. * M_PI_8)
		{
			direction_deplacement = BAS;
		}
		else if(m_angle_deplacement >= 9. * M_PI_8 && m_angle_deplacement < 11. * M_PI_8)
		{
			direction_deplacement = BAS_GAUCHE;
		}
		else if(m_angle_deplacement >= 11. * M_PI_8 && m_angle_deplacement < 13. * M_PI_8)
		{
			direction_deplacement = GAUCHE;
		}
		else if(m_angle_deplacement >= 13. * M_PI_8 && m_angle_deplacement < 15. * M_PI_8)
		{
			direction_deplacement = HAUT_GAUCHE;
		}
		
		// Test de collisions avec les tiles solides de la carte et modification du déplacement si il y a collision.
		coins[0] = carte.isTileSolide(m_position.x/largeur_tile, m_position.y/hauteur_tile);
		coins[1] = carte.isTileSolide((m_position.x+largeur_entite-1)/largeur_tile, m_position.y/hauteur_tile);
		coins[2] = carte.isTileSolide((m_position.x+largeur_entite-1)/largeur_tile, (m_position.y+hauteur_entite-1)/hauteur_tile);
		coins[3] = carte.isTileSolide(m_position.x/largeur_tile, (m_position.y+hauteur_entite-1)/hauteur_tile);
		if(coins[0] && coins[1]) {
			m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
		}
		if(coins[1] && coins[2]) {
			m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
		}
		if(coins[2] && coins[3]) {
			m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
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
			case DROITE: m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
				break;
			case HAUT: m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
				break;
			case HAUT_GAUCHE: m_position.y = (m_position.y/hauteur_tile + 1) * hauteur_tile;
				break;
			case BAS_DROITE: m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
				break;
			case HAUT_DROITE:
				if((m_position.x/largeur_tile)*largeur_tile - pos_precedente.x > pos_precedente.y - (m_position.y/hauteur_tile + 1) * hauteur_tile) {
					m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
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
			case DROITE: m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
				break;
			case BAS: m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
				break;
			case BAS_GAUCHE: m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
				break;
			case HAUT_DROITE: m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
				break;
			case BAS_DROITE:
				if((m_position.x/largeur_tile)*largeur_tile - pos_precedente.x > (m_position.y/hauteur_tile)*hauteur_tile - pos_precedente.y) {
					m_position.x = ((m_position.x + largeur_entite - 1) / largeur_tile) * largeur_tile - largeur_entite;
				} else {
					m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
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
			case BAS: m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
				break;
			case BAS_DROITE: m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
				break;
			case HAUT_GAUCHE: m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
				break;
			case BAS_GAUCHE:
				if(pos_precedente.x - (m_position.x/largeur_tile + 1)*largeur_tile > (m_position.y/hauteur_tile)*hauteur_tile - pos_precedente.y) {
					m_position.x = (m_position.x/largeur_tile + 1) * largeur_tile;
				} else {
					m_position.y = ((m_position.y + hauteur_entite - 1) / hauteur_tile) * hauteur_tile - hauteur_entite;
				}
				break;
			default:
				break;
			}
		}
	}
}


/* Retourne la direction de déplacement de l'entité (en radians).*/
double Entite::getDirectionDeplacement() const
{
	return m_angle_deplacement;
}

/* Retourne la direction de visée de l'entité (en radians).*/
double Entite::getDirectionVisee() const
{
	return m_angle_visee;
}

/* Retourne la hauteur de l'image de l'entité.*/
int Entite::getHauteurImage() const
{
	return m_image->getHauteur();
}

/* Retourne le pointeur vers l'image de l'entité.*/
Texture* Entite::getImage() const
{
	return m_image;
}

/* Retourne la largeur de l'image de l'entité.*/
int Entite::getLargeurImage() const
{
	return m_image->getLargeur();
}

/* Retourne la position de l'entité.*/
Coordonnees Entite::getPosition() const
{
	return m_position;
}

/* Retourne la structure qui contient les composatnes de la vitesse de l'entité.*/
Coordonnees Entite::getVitesse() const
{
	return m_vitesse;
}

/* Retourne la vitesse maximum de l'entité.*/
int Entite::getVitesseMax() const
{
	return m_vitesse_max;
}

/* Si l'entité est en mouvement.*/
bool Entite::seDeplace() const
{
	return m_se_deplace;
}

/* Permet de modifier la direction de déplacement de l'entité.*/
void Entite::setDirectionDeplacement(double p_direction_deplacement)
{
	m_angle_deplacement = p_direction_deplacement;
}

/* Permet de modifier la position de l'entité.*/
void Entite::setPosition(Coordonnees p_position)
{
	m_position = p_position;
}
//-------------------------------------