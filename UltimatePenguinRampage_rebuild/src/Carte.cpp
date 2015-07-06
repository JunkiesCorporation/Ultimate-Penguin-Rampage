#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Carte.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.*/
Carte::Carte()
{
	// Initialisation des attributs à des valeurs par défaut.
	m_depart_joueur = { 0, 0};
	m_hauteur = 0;
	m_id_tiles = NULL;
	m_largeur = 0;
}
//---------------------------------

// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Carte::~Carte()
{
	// Destruction des attributs non NULL.
	if(m_id_tiles != NULL)
	{
		for(int i = 0; i < m_largeur; i++)
		{
			delete[] m_id_tiles[i];
		}
		delete[] m_id_tiles;
	}
}
//---------------------------------

// Fonctions membres publiques
//---------------------------------
/* Lis le fichier associé à la carte et charge les informations.*/
bool Carte::charger(std::string chemin_fichier)
{
	// Chemin d'accès au Tileset de la carte.
	std::string chemin_tileset = "";
	
	// Chargement du fichier donné dans un flux d'entrée.
	std::ifstream fichier(chemin_fichier.c_str());
	
	// Ligne de lecture du fichier.
	std::string ligne = "";
	
	// Si le chargement a réussi.
	bool succes = true;
	
	//---------------------------------
	// Démarrage du chargement de la carte.
	
	// temp
	std::cout << "Ouverture du fichier " << chemin_fichier << std::endl;
	
	// Gestion de d'un échec potentiel du chargement du fichier.
	if(!fichier.is_open())
	{
		// Affichage d'un message d'erreur.
		std::cout << "Erreur : impossible de charger la carte depuis le fichier " << chemin_fichier << std::endl;
		
		// Le chargement a échoué.
		succes = false;
		goto fin;
	}
	else
	{
		// temp
		std::cout << "Ouverture reussie, lecture du fichier..." << std::endl;
		
		//-----------------------------
		// Lecture des [infos_carte]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[infos_carte]")
		{
			std::cout << "Erreur : [infos_carte] manquant dans : " << chemin_fichier << std::endl;
			succes = false;
			goto fin;
		}
		
		// Lecture de la largeur.
		fichier >> ligne; fichier >> ligne;
		m_largeur = atoi(ligne.c_str());
		
		// Lecture de la hauteur.
		fichier >> ligne; fichier >> ligne;
		m_hauteur = atoi(ligne.c_str());
		
		// Création de la grille de données.
		m_id_tiles = new int*[m_largeur];
		for(int i = 0; i < m_largeur; i++)
		{
			m_id_tiles[i] = new int[m_hauteur];
		}
		
		//-----------------------------
		// Lecture des [infos_joueur]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[infos_joueur]")
		{
			std::cout << "Erreur : [infos_joueur] manquant dans : " << chemin_fichier << std::endl;
			succes = false;
			goto fin;
		}
		
		// Lecture des coordonnées de départ du joueur.
		fichier >> ligne; fichier >> ligne;
		m_depart_joueur.x = atoi(c_str());
		fichier >> ligne;
		m_depart_joueur.y = atoi(c_str());
		
		//-----------------------------
		// Lecture du [tileset]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[tileset]")
		{
			std::cout << "Erreur : [tileset] manquant dans : " << chemin_fichier << std::endl;
			succes = false;
			goto fin;
		}
		
		// Lecture du chemin d'accès au Tileset.
		fichier >> ligne; fichier >> ligne;
		chemin_tileset = ligne;
		
		// Chargement du Tileset.
		m_tileset.charger(chemin_tileset);
		
		//-----------------------------
		// Lecture des [donnees]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[donnees]")
		{
			std::cout << "Erreur : [donnees] manquant dans : " << chemin_fichier << std::endl;
			succes = false;
			goto fin;
		}
		
		// Lecture des données de la carte.
		for(int y = 0; y < m_hauteur; y++)
		{
			for(int x = 0; x < m_largeur; x++)
			{
				fichier >> ligne;
				m_id_tiles[x][y] = atoi(ligne.c_str());
			}
		}
		
		//-----------------------------
		// Fermeture du fichier.
		fichier.close();
		
		// temp
		std::cout << "Fichier " << chemin_fichier << " ferme." << std::endl;
	}
	
	fin:
	return succes;
}

/* Réinitialise la carte.*/
void Carte::reinitialiser()
{
	// Libération des éléments chargés.
	m_tileset.reinitialiser();
	
	// Réinitialisation des attributs à des valeurs par défaut.
	m_depart_joueur = { 0, 0};
	m_hauteur = 0;
	// Suppression correcte de la grille allouée dynamiquement.
	if(m_id_tiles != NULL)
	{
		for(int i = 0; i < m_largeur; i++)
		{
			delete[] m_id_tiles[i];
		}
		delete[] m_id_tiles;
	}
	m_largeur = 0;
	
	// temp
	std::cout << "Carte reinitialisee." << std::endl;
}
//---------------------------------

// Fonctions membres privées
//---------------------------------
//---------------------------------