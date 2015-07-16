#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entite.h"
#include "Carte.h"

/** La classe qui décrit les projectiles du jeu.
 */
class Projectile : public Entite
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Appel Entite::Entite().
		 *
		 * Initialise les attributs à des valeurs par défaut.
		 */
		Projectile();
		
		/** Constructeur de chargement.
		 *
		 * Permet de charger le projectile à partir du fichier correspondant à l'id et au nom donné. Utilisé lors du chargement de la liste de projectiles.
		 *
		 * @param p_id L'id du projectile à charger.
		 * @param p_nom_fichier Le nom du fichier correspondant au projectile à charger.
		 */
		Projectile(int p_id, std::string const &p_nom_fichier);
		
		/** Constructeur de copie.
		 *
		 * Permet de créer une nouvelle instance de Projectile identique à celle donnée en paramètre.
		 *
		 * @param projectile Le Projectile à copier.
		 */
		Projectile(Projectile const &projectile);
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 *
		 * Appel Entite::~Entite().
		 *
		 * Supprime les attributs non nuls.
		 */
		~Projectile();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Met à jour le projectile.
		 *
		 * @param carte La carte sur laquelle le projectile évolue.
		 * @sa Entite::update().
		 */
		void update(Carte const &carte);
		
		/** Retourne si le projectile est hors des frontières de la carte.
		 *
		 * @return #m_hors_carte Si le projectile est hors de la carte.
		 */
		bool estHorsCarte() const;
		
		/** Retourne l'id du projectile.
		 *
		 * @return #m_id L'id du projectile.
		 */
		int getID() const;
		//-----------------------------
	
	protected:
	
	private:
		// Types privés
		//-----------------------------
		/** Mot-clef permettant l'accès rapide aux méthodes d'Entite.
		 */
		typedef Entite super;
		//-----------------------------
		
		// Attributs privés
		//-----------------------------
		/** Le numéro unique d'identification du projectile.
		 */
		int m_id;
		
		/** Si le projectile est sorti des frontières de la carte.
		 */
		bool m_hors_carte;
		//-----------------------------
};

#endif // PROJECTILE_H