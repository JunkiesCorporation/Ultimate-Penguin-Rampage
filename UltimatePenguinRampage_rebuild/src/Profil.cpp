#include <iostream>

#include "Profil.h"
#include "Texture.h"

/* Constructeur par défaut.*/
Profil::Profil()
{
	premiere_fois = true;
	emplacement_sauvegarde = 0;
	nom_du_profil = "Debug";
	
	std::cout << "Profil cree." << std::endl;
}

/* Constructeur permettant la configuration d'un profil.*/
Profil::Profil(bool p_premiere_fois)
{
	// Si c'est la première fois, création d'un nouveau profil avec choix d'un emplacement de sauvegarde.
	if(p_premiere_fois)
	{
		
	}
	// Sinon, chargement d'un profil existant après la sélection d'un emplacement de sauvegarde.
	else
	{
		
	}
}

/* Destructeur par défaut.*/
Profil::~Profil()
{
	std::cout << "Profil " << nom_du_profil << " detruit." << std::endl;
}