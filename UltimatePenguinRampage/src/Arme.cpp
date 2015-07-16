#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Arme.h"
#include "Utils.h"
#include "Arene.h"
#include "Jeu.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Arme::Arme() : m_id(0), m_id_projectile(0), m_nom(""), m_tps_recharge(10), m_type(ARME_CORPS_A_CORPS)
{
	// Aucun attribut à initialiser.
	
	// temp
	std::cout << "Arme construite par defaut." << std::endl;
}

/* Constructeur de chargement.*/
Arme::Arme(int p_id, std::string const &p_nom_fichier) : m_tps_recharge(10)
{
	// Le chemin d'accès au fichier de l'arme.
	std::string chemin_fichier = "";
	
	// Le flux d'entrée pour charger le fichier de l'arme.
	std::ifstream fichier;

	// Ligne de lecture du fichier.
	std::string ligne = "";
	
	// Numéro d'id temporaire pour vérification.
	int temp_id = 0;
	
	//---------------------------------
	// Démarrage du chargement de l'arme.
	
	// Création du chemin d'accès au fichier.
	chemin_fichier = "rsc/obj/armes/" + intVersString(p_id) + "_" + p_nom_fichier + ".txt";
	
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
		// Lecture des [infos_arme]
		
		// Gestion d'un échec potentiel;
		fichier >> ligne;
		if(ligne != "[infos_arme]")
		{
			// Affichage d'un message d'erreur.
			std::cout << "Erreur : [infos_arme] manquant dans le fichier " << chemin_fichier << std::endl;
			
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
			std::cout << "Erreur : incoherence des numeros d'id de l'arme " << p_nom_fichier << " dans le fichier " << chemin_fichier << std::endl;
			
			// On arrête le chargment.
			goto close;
		}
		
		m_id = temp_id;
		
		// Lecture du nom de l'arme.
		fichier >> ligne; fichier >> ligne;
		m_nom = remplacerParEspaces(ligne);
		
		// Lecture du type de l'arme.
		fichier >> ligne; fichier >> ligne;
		for(int i = 0; i < NB_TYPES_ARMES; i++)
		{
			if(ligne == type_armes_string[ARME_CORPS_A_CORPS])
			{
				m_type = ARME_CORPS_A_CORPS;
				break;
			}
			else if(ligne == type_armes_string[ARME_DE_JET])
			{
				m_type = ARME_DE_JET;
				break;
			}
		}
		
		// Récupération des informations correspondant au type de l'arme.
		if(m_type == ARME_DE_JET)
		{
			//-------------------------
			// Lecture des [infos_arme_de_jet]
			
			// Gestion d'un échec potentiel
			fichier >> ligne;
			if(ligne != "[infos_arme_de_jet]")
			{
				// Affichage d'un message d'erreur.
				std::cout << "Erreur : [infos_arme_de_jet] manquant dans le fichier " << chemin_fichier << std::endl;
				
				// On arrête le chargement.
				goto close;
			}
			
			// Lecture de l'id du projectile tiré.
			fichier >> ligne; fichier >> ligne;
			m_id_projectile = atoi(ligne.c_str());
		}
		
		// temp
		std::cout << "Arme construite par chargement." << std::endl;
		std::cout << "    id : " << m_id << " nom : " << m_nom << std::endl;
		
		// Fermeture du fichier.
		close:
		fichier.close();
	}
}

/* Constructeur de copie.*/
Arme::Arme(Arme const &arme) : m_id(arme.getID()), m_nom(arme.getNom()), m_tps_recharge(10), m_type(arme.getType())
{
	// Aucun attribut à initialise.
	
	// temp
	std::cout << "Arme construite par copie." << std::endl;
}
//-------------------------------------

// Destructeur
//-------------------------------------
/* Destructeur par défaut.*/
Arme::~Arme()
{
	// Aucun attribut à détruire.
	
	// temp
	std::cout << "Arme detruite." << std::endl;
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Enclenche l'utilisation de l'arme.*/
void Arme::utiliser(Entite const &entite)
{
	// temp
	std::cout << "Arme utilisee." << std::endl;
	
	// Utilisations différentes en fonction du type de l'arme.
	switch(m_type)
	{
	case ARME_DE_JET:
		// Récupération de l'exemplaire du projectile.
		Projectile temp_projectile(Jeu::getProjectileDepuisID(m_id_projectile));
		
		// Initialisation de la direction de déplacement et de la position du projectile.
		temp_projectile.setDirectionDeplacement(entite.getDirectionVisee());
		temp_projectile.setPosition(entite.getPosition());
		
		// Récupération du projectile et ajout dans l'arène.
		Arene::ajouterProjectile(temp_projectile);
		break;
	}
}

/* Retourne l'id de l'arme.*/
int Arme::getID() const
{
	return m_id;
}

/* Retourne le nom de l'arme.*/
std::string Arme::getNom() const
{
	return m_nom;
}

/* Retourne le temps de recharge de l'arme.*/
int Arme::getTpsRecharge() const
{
	return m_tps_recharge;
}

/* Retourne le type de l'arme.*/
TypeArme Arme::getType() const
{
	return m_type;
}
//-------------------------------------