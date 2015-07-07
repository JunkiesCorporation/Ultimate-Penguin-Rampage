#include <iostream>

#include "Joueur.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.
 *
 * Appel explicitement le constructeur par défaut d'Entité.
 */
Joueur::Joueur() : super()
{
	// Aucun attribut à initialiser.
	
	// temp
	std::cout << "Joueur creer." << std::endl;
}
//---------------------------------

// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Joueur::~Joueur()
{
	// Aucun attribut à détruire.
	
	// temp
	std::cout << "Joueur detruit." << std::endl;
}
//---------------------------------

// Fonctions membres publiques
//---------------------------------
/* Met à jour le joueur.*/
void Joueur::update()
{
	// Pas d'instructions de mise-à-jour.
}
//---------------------------------