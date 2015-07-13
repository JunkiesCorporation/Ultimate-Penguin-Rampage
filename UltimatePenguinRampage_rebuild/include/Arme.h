#ifndef ARME_H
#define ARME_H

#include <string>

/** Modèle de toutes armes du jeu.
 *
 * Assure leur fonctionnement ainsi que leur affichage à l'écran.
 */
class Arme
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs à des valeurs par défaut.
		 */
		Arme();
		
		/** Constructeur de chargement.
		 *
		 * Permet de charger l'arme à partir du fichier correspondant à l'id et au nom donné. Utilisé lors du chargement de la liste d'arme.
		 *
		 * @param p_id L'id de l'arme à charger.
		 * @param p_nom_fichier Le nom du fichier correspondant à l'arme à charger.
		 */
		Arme(int p_id, std::string const &p_nom_fichier);
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 *
		 * Détruit les attributs non nuls.
		 */
		~Arme();
		//-----------------------------
		
	protected:
	
	private:
		// Attributs privés
		//-----------------------------
		/** Le numéro unique d'identification de l'arme.
		 */
		int m_id;
		
		/** Le nom de l'arme, tel qu'il apparaît à l'écran.
		 */
		std::string m_nom;
		//-----------------------------
	
};

#endif // ARME_H