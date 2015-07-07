#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"

class Joueur : public Entite
{
	public:
		// Constructeurs
		//---------------------------------
		/** Constructeur par défaut.
		 * 
		 * Appel Entite::Entite().
		 *
		 * Initialise les attributs à des valeurs pas défaut.
		 */
		Joueur();
		//---------------------------------
		
		// Destructeur
		//---------------------------------
		/** Destructeur par défaut.
		 *
		 * Appel Entite::~Entite().
		 *
		 * Supprime les attributs non nuls.
		 */
		~Joueur();
		//---------------------------------
		
		// Fonctions membres publiques
		//---------------------------------
		/** Met à jour le joueur.
		 *
		 * @sa Entite::update().
		 */
		void update();
		//---------------------------------
	
	protected:
	
	private:
		// Types privés
		//---------------------------------
		/** Mot-clef permettant l'accès rapide aux méthodes d'Entite.
		 */
		typedef Entite super;
		//---------------------------------
		
		// Attributs privés
		//---------------------------------
		//---------------------------------
	
};

#endif // JOUEUR_H