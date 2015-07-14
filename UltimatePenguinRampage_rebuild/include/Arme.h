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
		
		/** Constructeur de copie.
		 *
		 * Permet de créer une nouvelle instance de Arme identique à celle donnée en paramètre.
		 *
		 * @param arme L'arme à copier.
		 */
		Arme(Arme const &arme);
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 *
		 * Détruit les attributs non nuls.
		 */
		~Arme();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Retourne l'id de l'arme.
		 *
		 * @return #m_id L'id de l'arme.
		 */
		int getID() const;
		
		/** Retourne le nom de l'arme.
		 *
		 * @return m_nom Le nom de l'arme.
		 */
		std::string getNom() const;
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