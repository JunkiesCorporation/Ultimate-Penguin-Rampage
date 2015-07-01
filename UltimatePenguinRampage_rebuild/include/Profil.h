#ifndef PROFIL_H
#define PROFIL_H

#include <string>

/** Classe du profil du joueur.
 * \todo description de Profil.
 */
class Profil
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 * Initialise les attributs membres de Profil à des valeurs par défaut.
		 */
		Profil();
		
		/** Constructeur permettant la configuration d'un profil.
		 * @param p_premiere_fois Si il s'agit d'un nouveau profil ou non. Détermine si le constructeur créé un nouveau profil ou en un charge un déjà existant.
		 */
		Profil(bool p_premiere_fois);
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 */
		~Profil();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		//-----------------------------
	
	protected:
	
	private:
		// Attributs membres privés.
		//-----------------------------
		/** Numéro de l'emplacement de sauvegarde de ce profil.
		 */
		int emplacement_sauvegarde;
		
		/** Le nom du profil.
		 */
		std::string nom_du_profil;
		
		/** S'il s'agit de la première fois que ce profil est utilisé.
		 */
		bool premiere_fois;
		//-----------------------------
};

#endif // PROFIL_H