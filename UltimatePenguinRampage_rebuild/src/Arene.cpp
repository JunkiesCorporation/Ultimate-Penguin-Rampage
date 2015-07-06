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
	// Chargement de la carte et gestion d'un échec potentiel.
	// temp
	std::cout << "Chargement de la Carte..." << std::endl;
	if(!m_carte.charger("rsc/map/carte_test_1.txt"))
	{
		// temp
		std::cout << "Chargement de l'arene interrompu : le chargement de la carte a echoue." << std::endl;
		
		m_est_prete = false;
		return;
	}
	// temp
	std::cout << "Carte chargee avec succes." << std::endl;
	
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

/* Réinitialise une arène lancée et terminée.*/
void Arene::reinitialiser()
{
	// Réinitialisation de la carte.
	m_carte.reinitialiser();
	
	// temp
	std::cout << "Arene reinitialisee." << std::endl;
	
	// Indication que l'arène n'est plus prête à être lancée.
	m_est_prete = false;
}
//---------------------------------