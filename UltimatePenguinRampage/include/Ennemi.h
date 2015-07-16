#ifndef ENNEMI_H
#define ENNEMI_H

#include "Entite.h"

/** Classe qui gère les ennemis.
 */
class Ennemi : public Entite
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs à des valeurs par défaut.
		 *
		 * @sa Entite::Entite().
		 */
		Ennemi();
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 *
		 * Supprime tout les attributs non nuls.
		 */
		~Ennemi();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Met à jour l'ennemi.
		 *
		 * @sa Entite::update().
		 */
		void update(Carte const &carte);
		//-----------------------------
		
	private:
		// Types privés
		//-----------------------------
		/** Mot-clef permettant l'accès rapide aux méthodes d'Entite.
		 */
		typedef Entite super;
		//-----------------------------
};

#endif // ENNEMI_H