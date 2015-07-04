#include <iostream>

#include "Arene.h"

// Constructeurs
//---------------------------------
/* Constructeur par défaut.*/
Arene::Arene()
{
	// Initialisation des attributs à des valeurs par défaut.
	m_est_prete = false;
}
//---------------------------------

// Destructeur
//---------------------------------
/* Destructeur par défaut.*/
Arene::~Arene()
{
	// Aucun attribut à détruire.
}
//---------------------------------

// Fonctions membres publiques
//---------------------------------
/* Charge les éléments requis pour le fonctionnement de cette instance d'Arene.*/
void Arene::charger()
{
	// temp
	std::cout << "Chargement de l'arene termine." << std::endl;
	
	// Indication que l'arène est prête à être lancée.
	m_est_prete = true;
}

/* Lance l'arène si elle a été précédemment préparée à l'aide de #charger().*/
void Arene::lancer()
{
	// Vérification si l'arène est prête à être lancée.
	if(!m_est_prete)
	{
		/** \todo Affichage d'un message d'erreur si on tente le lancement d'une instance d'Arene qui n'est pas prête.*/
		// temp
		std::cout << "Erreur : tentative de lancement d'une arène incorrectement preparee." << std::endl;
		return;
	}
	
	// temp
	std::cout << "Lancement de l'arene..." << std::endl;
}

/* Ré-initialise une arène lancée et terminée.*/
void Arene::reinitialiser()
{
	// temp
	std::cout << "Arene re-initialisee." << std::endl;
	
	// Indication que l'arène n'est plus prête à être lancée.
	m_est_prete = false;
}
//---------------------------------