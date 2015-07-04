#include <fstream>

#include "Carte.h"

// Constructeurs
//---------------------------------
/* Constructeur avec chemin d'accès au fichier contenant les données de la carte.*/
Carte::Carte(std::string chemin_fichier)
{
	// Initialisation des attributs à des valeurs par défaut.
	// Aucun attribut à initialiser.
	
	// Chargement des informations de la carte à partir du fichier donné.
	charger(chemin_fichier);
}
//---------------------------------

// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Carte::~Carte()
{
	// Aucun attribut à détruire.
}
//---------------------------------

// Fonctions membres publiques
//---------------------------------
//---------------------------------

// Fonctions membres privées
//---------------------------------
/* Lis le fichier associé à la carte et charge les informations.*/
void Carte::charger(std::string chemin_fichier)
{
	// Chargement du fichier donné dans un flux d'entrée.
	std::ifstream fichier(chemin_fichier.c_str());
	
	// Ligne de lecture du fichier.
	std::string ligne = "";
	
	//---------------------------------
	// Démarrage du chargement de la carte.
	
	if(fichier)
	{
		
	}
	else
	{
		
	}
}
//---------------------------------