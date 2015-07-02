#include <iostream>

#include "Profil.h"
#include "Texture.h"

// Constructeurs
//-------------------------------------
/* Constructeur par défaut.*/
Profil::Profil()
{
	m_emplacement_sauvegarde = 0;
	
	m_nom_du_profil = "";
	
	m_nouveau = true;
}
//-------------------------------------

// Destructeur
//-------------------------------------
/* Destructeur par défaut.*/
Profil::~Profil()
{
	std::cout << "Profil " << m_nom_du_profil << " detruit." << std::endl;
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Change l'emplacement de sauvegarde du profil.*/
void Profil::setEmplacementSauvegarde(int p_emplacement_sauvegarde)
{
	m_emplacement_sauvegarde = p_emplacement_sauvegarde;
}

/* Change le nom du profil.*/
void Profil::setNomProfil(std::string p_nom_du_profil)
{
	m_nom_du_profil = p_nom_du_profil;
}

/* Change s'il s'agit d'un nouveau profil ou non.*/
void Profil::setSiNouveau(bool p_nouveau)
{
	m_nouveau = p_nouveau;
}
//-------------------------------------