#include "Entite.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.*/
Entite::Entite() : m_direction_deplacement(M_PI), m_direction_visee(M_PI), m_image(NULL), m_vitesse_max(0)
{
	// Initialisation des attributs à des valeurs par défaut.
	m_position.x = 0;
	m_position.y = 0;
	m_vitesse.x = 0;
	m_vitesse.y = 0;
}

/* Constructeur avec position.*/
Entite::Entite(Coordonnees pos_depart) : m_direction_deplacement(M_PI), m_direction_visee(M_PI), m_image(NULL), m_vitesse_max(0)
{
	// Initialisation des attributs
	m_position.x = pos_depart.x;
	m_position.y = pos_depart.y;
	m_vitesse.x = 0;
	m_vitesse.y = 0;
}

/* Constructeur de copie.*/
Entite::Entite(Entite const &entite) : m_direction_deplacement(entite.getDirectionDeplacement()), m_direction_visee(entite.getDirectionVisee()), m_image(NULL), m_position(entite.getPosition()), m_vitesse(entite.getVitesse()), m_vitesse_max(entite.getVitesseMax())
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

/* Retourne la direction de déplacement de l'entité (en radians).*/
double Entite::getDirectionDeplacement() const
{
	return m_direction_deplacement;
}

/* Retourne la direction de visée de l'entité (en radians).*/
double Entite::getDirectionVisee() const
{
	return m_direction_visee;
}

/* Retourne la hauteur de l'image de l'entité.*/
int Entite::getHauteurImage() const
{
	return m_image->getHauteur();
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

/* Permet de modifier la direction de déplacement de l'entité.*/
void Entite::setDirectionDeplacement(double p_direction_deplacement)
{
	m_direction_deplacement = p_direction_deplacement;
}

/* Permet de modifier la position de l'entité.*/
void Entite::setPosition(Coordonnees p_position)
{
	m_position = p_position;
}
//-------------------------------------