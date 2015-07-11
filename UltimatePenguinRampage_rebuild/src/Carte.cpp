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
			delete m_id_tiles[i];
		}
		delete m_id_tiles;
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
		m_depart_joueur.x = atoi(ligne.c_str());
		fichier >> ligne;
		m_depart_joueur.y = atoi(ligne.c_str());
		
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
		if(!m_tileset.charger(chemin_tileset))
		{
			// temp
			std::cout << "Erreur : impossible de charger le tileset " << chemin_tileset << " de la carte " << chemin_fichier << std::endl;
			
			succes = false;
			goto fin;
		}
		
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
	m_id_tiles = NULL;
	m_largeur = 0;
	
	// temp
	std::cout << "Carte reinitialisee." << std::endl;
}

/* Affiche les tiles de la carte qui se trouvent sous la caméra.*/
void Carte::render(SDL_Rect camera) const
{
	// Récupération des dimensions d'une tile.
	int largeur_tile = m_tileset.getLargeurTile();
	int hauteur_tile = m_tileset.getHauteurTile();
	
	// Définissent le rectangle qui couvre toutes les tiles à afficher (en tiles)
	Coordonnees pos_haut_gauche = { 0, 0};
	Coordonnees pos_bas_droite = { 0, 0};
	
	// Attribution des dimensions du rectangle.
	pos_haut_gauche.x = camera.x / largeur_tile;
	pos_haut_gauche.y = camera.y / hauteur_tile;
	pos_bas_droite.x = ((camera.x + camera.w) / largeur_tile) + 1;
	pos_bas_droite.y = ((camera.y + camera.h) / hauteur_tile) + 1;
	
	// Il ne faut que pas que l'on accède à des tiles en-dehors de la carte.
	if(pos_haut_gauche.x < 0) { pos_haut_gauche.x = 0; }
	if(pos_haut_gauche.x > m_largeur) { pos_haut_gauche.x = m_largeur - (camera.w / largeur_tile); }
	if(pos_haut_gauche.y < 0) { pos_haut_gauche.y = 0; }
	if(pos_haut_gauche.y > m_hauteur) { pos_haut_gauche.y = m_hauteur - (camera.h / hauteur_tile); }
	if(pos_bas_droite.x > m_largeur) { pos_bas_droite.x = m_largeur; }
	if(pos_bas_droite.x < 0) { pos_bas_droite.x = camera.w / largeur_tile; }
	if(pos_bas_droite.y > m_hauteur) {pos_bas_droite.y = m_hauteur; }
	if(pos_bas_droite.y < 0) {pos_bas_droite.y = camera.h / hauteur_tile; }
	
	// Affichage des tiles contenues dans le rectangle agrandi.
	for(int y = pos_haut_gauche.y; y < pos_bas_droite.y; y++)
	{
		for(int x = pos_haut_gauche.x; x < pos_bas_droite.x; x++)
		{
			m_tileset.render(m_id_tiles[x][y], x * largeur_tile - camera.x, y * hauteur_tile - camera.y);
		}
	}
	
}

/* Retourne si la tile à la position indiquée est solide ou non.*/
bool Carte::isTileSolide(int x, int y) const {
    return m_tileset.isTileSolide(m_id_tiles[x][y]);
}

/* Retourne la hauteur d'une tile sur la carte.*/
int Carte::getHauteurTile() const
{
	return m_tileset.getHauteurTile();
}

/* Retourne la largeur d'une tile sur la carte.*/
int Carte::getLargeurTile() const
{
	return m_tileset.getLargeurTile();
}

/* Retourne la position de départ du joueur.*/
Coordonnees Carte::getPositionDepartJoueur() const
{
	// Conversion des unités des coordonnées.
	Coordonnees temp = { m_depart_joueur.x * m_tileset.getLargeurTile(), m_depart_joueur.y * m_tileset.getHauteurTile()};
	
	return temp;
}
//---------------------------------

// Fonctions membres privées
//---------------------------------
//---------------------------------