#include <iostream>
#include <fstream>

#include "Projectile.h"
#include "Utils.h"
#include "Jeu.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Projectile::Projectile() : super(), m_id(0), m_hors_carte(false)
{
	// Aucun attribut à initialiser.
	
	// temp
	std::cout << "Projectile construit par defaut." << std::endl;
}

/* Constructeur de chargement.*/
Projectile::Projectile(int p_id, std::string const &p_nom_fichier) : super(), m_hors_carte(false)
{
	// Le chemin d'accès au fichier du projectile.
	std::string chemin_fichier = "";
	
	// Le flux d'entrée pour charger le fichier de l'arme.
	std::ifstream fichier;
	
	// Ligne de lecture du fichier.
	std::string ligne = "";
	
	// Numéro d'id temporaire pour vérification.
	int temp_id = 0;
	
	//---------------------------------
	// Démarrage du chargement du projectile.
	
	// Création du chemin d'accès au fichier.
	chemin_fichier = "rsc/obj/projectiles/" + intVersString(p_id) + "_" + p_nom_fichier + ".txt";
	
	// Ouverture du fichier.
	fichier.open(chemin_fichier);
	
	// Gestion d'un échec potentiel.
	if(!fichier.is_open())
	{
		// Affichage d'un message d'erreur.
		std::cout << "Erreur : impossible d'ouvrir le fichier " << chemin_fichier << std::endl;
	}
	else
	{
		//-----------------------------
		// Lecture des [infos_projectile]
		
		// Gestion d'un échec potentiel;
		fichier >> ligne;
		if(ligne != "[infos_projectile]")
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : [infos_projectile] manquant dans le fichier " << chemin_fichier << std::endl;
			
			// On arrête le chargement.
			goto close;
		}
		
		// Lecture du numéro d'id indiqué dans le fichier.
		fichier >> ligne; fichier >> ligne;
		temp_id = atoi(ligne.c_str());
		
		// Vérification que les numéro d'id soient les mêmes.
		if(temp_id != p_id)
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : incoherence des numeros d'id du projectile " << p_nom_fichier << " dans le fichier " << chemin_fichier << std::endl;
			
			// On arrête le chargment.
			goto close;
		}
		
		m_id = temp_id;
		
		// temp
		std::cout << "Projectile construit par chargement." << std::endl;
		std::cout << "    id : " << m_id << std::endl;
		
		// Fermeture du fichier.
		close:
		fichier.close();
	}
}

/* Constructeur de copie.*/
Projectile::Projectile(Projectile const &projectile) : super(projectile), m_id(projectile.getID()), m_hors_carte(projectile.estHorsCarte())
{
	// Aucun attribut à initialise.
	
	// temp
	m_image = &Jeu::textureBouleDeNeige;
	
	// temp
	m_vitesse_max = 6;
	
	// temp
	m_se_deplace = true;
	
	// temp
	std::cout << "Projectile construit par copie." << std::endl;
}
//-------------------------------------

// Destructeur
//-------------------------------------
/* Destructeur par défaut.*/
Projectile::~Projectile()
{
	// Aucun attribut à détruire.
	
	// temp
	m_image = NULL;
	
	// temp
	std::cout << "Projectile detruit." << std::endl;
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Met à jour le projectile.*/
void Projectile::update(Carte const &carte)
{
	// Appel à Entite::update().
	super::update(carte);
	
	if(m_position.x + m_image->getHauteur() < 0 || m_position.y + m_image->getLargeur() < 0 || m_position.x > carte.getLargeur() * carte.getLargeurTile() || m_position.y > carte.getHauteur() * carte.getHauteurTile())
	{
		m_hors_carte = true;
	}
}

/* Retourne si le projectile est hors des frontières de la carte.*/
bool Projectile::estHorsCarte() const
{
	return m_hors_carte;
}

/* Retourne l'id du projectile.*/
int Projectile::getID() const
{
	return m_id;
}
//-------------------------------------