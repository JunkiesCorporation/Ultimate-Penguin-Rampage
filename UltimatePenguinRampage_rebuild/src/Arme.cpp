#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Arme.h"
#include "Utils.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Arme::Arme() : m_id(0), m_nom("")
{
	// Aucun attribut à initialiser.
}

/* Constructeur de chargement.*/
Arme::Arme(int p_id, std::string const &p_nom_fichier)
{
	// Le chemin d'accès au fichier de l'arme.
	std::string chemin_fichier;
	
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
		
		// Lecture du nom de l'arme.
		fichier >> ligne; fichier >> ligne;
		m_nom = remplacerParEspaces(ligne);
		
		// temp
		std::cout << "Arme chargee avec succes." << std::endl;
		
		// Fermeture du fichier.
		close:
		fichier.close();
	}
}
//-------------------------------------

// Destructeur
//-------------------------------------
/* Destructeur par défaut.*/
Arme::~Arme()
{
	// Aucun attribut à détruire.
}
//-------------------------------------