#include <fstream>
#include <iostream>

#include "Tileset.h"
#include "UPR.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Tileset::Tileset()
{
	// Initialisation des attributs à des valeurs par défaut.
	m_hauteur = 0;
	m_hauteur_tile = 0;
	m_image = NULL;
	m_largeur = 0;
	m_largeur_tile = 0;
	m_tiles = NULL;
}
//-------------------------------------

// Destructeur
//-------------------------------------
/* Destructeur par défaut.*/
Tileset::~Tileset()
{	
	// Destruction des attributs non nuls.
	delete m_image;
	m_image = NULL;
	
	delete[] m_tiles;
	m_tiles = NULL;
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Lis le fichier donné associé au Tileset et charge les informations.*/
bool Tileset::charger(std::string chemin_fichier)
{
	// Chemin d'accès à l'image du Tileset.
	std::string chemin_image = "";
	
	// Chargement du fichier donné dans un flux d'entrée.
	std::ifstream fichier(chemin_fichier.c_str());
	
	// Ligne de lecture du fichier.
	std::string ligne = "";
	
	// Si le chargement a réussi.
	bool succes = true;
	
	//---------------------------------
	// Démarrage du chargement du tileset.
	
	// temp
	std::cout << "Ouverture du fichier " << chemin_fichier << std::endl;
	
	// Gestion de d'un échec potentiel du chargement du fichier.
	if(!fichier.is_open())
	{
		// Affichage d'un message d'erreur.
		std::cout << "Erreur : impossible de charger le tileset depuis le fichier " << chemin_fichier << std::endl;
		
		// Le chargement a échoué.
		succes = false;
		goto fin;
	}
	else
	{
		// temp
		std::cout << "Ouverture reussie, lecture du fichier..." << std::endl;
		
		//-----------------------------
		// Lecture des [infos_tileset]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[infos_tileset]")
		{
			std::cout << "Erreur : [infos_tileset] manquant dans : " << chemin_fichier << std::endl;
			succes = false;
			goto fin;
		}
		
		// Lecture de la largeur du tileset.
		fichier >> ligne; fichier >> ligne;
		m_largeur = atoi(ligne.c_str());
		
		// Lecture de la hauteur du tileset.
		fichier >> ligne; fichier >> ligne;
		m_hauteur = atoi(ligne.c_str());
		
		// Lecture de la largeur d'une tile.
		fichier >> ligne; fichier >> ligne;
		m_largeur_tile = atoi(ligne.c_str());
		
		// Lecture de la hauteur d'une tile.
		fichier >> ligne; fichier >> ligne;
		m_hauteur_tile = atoi(ligne.c_str());
		
		// Lecture du chemin d'accès à l'image du tileset.
		fichier >> ligne; fichier >> ligne;
		chemin_image = ligne;
		
		// Chargement de l'image du tileset et gestion d'un échec potentiel.
		m_image = new Texture(chemin_image.c_str());
		if(!m_image)
		{
			// temp
			std::cout << "Erreur : impossible de charger l'image " << chemin_image << " du Tileset " << chemin_fichier << std::endl;
			
			succes = false;
			goto fin;
		}
		
		// Création du tableau de tiles.
		m_tiles = new Tile[m_largeur * m_hauteur];
		
		// Initialisation du tableau de tiles.
		int id_tile = 0;
		for(int y = 0; y < m_hauteur; y++)
		{
			for(int x = 0; x < m_largeur; x++)
			{
				// Calcul de l'ID de la tile.
				id_tile = x + y * 10 + 1;
				
				// Attribution de l'ID de la tile.
				m_tiles[id_tile - 1].id_tile = id_tile;
				
				// Attribution des caractéristiques du rectangle de découpage.
				m_tiles[id_tile - 1].rect_clip.x = x * m_largeur_tile;
				m_tiles[id_tile - 1].rect_clip.y = y * m_hauteur_tile;
				m_tiles[id_tile - 1].rect_clip.w = m_largeur_tile;
				m_tiles[id_tile - 1].rect_clip.h = m_hauteur_tile;
				
				// Attribution d'un type de tile par défaut.
				m_tiles[id_tile - 1].type = TILE_TRAVERSABLE;
			}
		}
		
		//-----------------------------
		// Lecture des [tiles_solides]
		
		// Gestion d'un échec potentiel.
		fichier >> ligne;
		if(ligne != "[tiles_solides]")
		{
			std::cout << "Erreur : [tiles_solides] manquant dans : " << chemin_fichier << std::endl;
			succes = false;
			goto fin;
		}
		
		// Lecture du nombre de tiles solides.
		fichier >> ligne; fichier >> ligne;
		int nombre_tiles_solides = atoi(ligne.c_str());
		
		// Lecture des ID des tiles solides.
		for(int i = 0; i < nombre_tiles_solides; i++)
		{
			fichier >> ligne;
			m_tiles[atoi(ligne.c_str()) - 1].type = TILE_SOLIDE;
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
	
/* Réinitialise le Tileset.*/
void Tileset::reinitialiser()
{
	// Libération des éléments chargés.
	delete m_image;
	m_image = NULL;
	
	// Réinitialisation des attributs à des valeurs par défaut.
	m_hauteur = 0;
	m_hauteur_tile = 0;
	m_largeur = 0;
	m_largeur_tile = 0;
	// Suppression correcte du tableau alloué dynamiquement.
	delete[] m_tiles;
	m_tiles = NULL;
	
	// temp
	std::cout << "Tileset reinitialise." << std::endl;
}

/* Affiche la tile donnée aux coordonnées indiquées.*/
void Tileset::render(int id_tile, int x, int y) const
{
	// Le rectangle sur lequel la texture est projetée.
	SDL_Rect render_quad = {x, y, m_largeur_tile, m_hauteur_tile};
	
	// L'instruction pour afficher la texture.
	SDL_RenderCopy(UPR::renderer_SDL, m_image->getImage(), &m_tiles[id_tile - 1].rect_clip, &render_quad);
}

/* Retourne si la tile indiquée est solide ou non.*/
bool Tileset::isTileSolide(int tileID) const {
    return m_tiles[tileID-1].type == TILE_SOLIDE;
}

/* Retourne la largeur d'une tile du tileset.*/
int Tileset::getLargeurTile() const
{
	return m_largeur_tile;
}

/* Retourne la hauteur d'une tile du tileset.*/
int Tileset::getHauteurTile() const
{
	return m_hauteur_tile;
}
//-------------------------------------