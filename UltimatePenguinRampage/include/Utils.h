#ifndef UTILS_H
#define UTILS_H

#include <string>

/** Regroupe quelques fonctions d'utilité générale.
 */
class Utils
{
	public:
		// Fonctions membres publiques
		//-----------------------------
		/** Initialise la SDL et ses principaux composants.
		 *
		 * @return TRUE si l'initialisation s'est correctement déroulée.
		 * @return FALSE si il y a eu un problème avec l'initialisation de la SDL.
		 */
		static bool initialisationSDL(); 
		
		/** Détruit les composants restants de la SDL et quitte correctement les systèmes ouverts.
		 */
		static void quitterSDL();
		//-----------------------------
	
	protected:
	
	private:
	
};

/** Converti le nombre donnée en un objet string qui contient sa représentation en texte.
 *
 * @param p_nombre Le nombre à convertir.
 *
 * @return L'objet string contenant la représentation texte du nombre.
 */
std::string intVersString(int const& p_nombre);

/** Remplace tous les tirets bas '_' par des espaces ' ' dans le texte donné.
 *
 * @param p_texte Le texte à modifier.
 *
 * @return Le texte modifié.
 */
std::string remplacerParEspaces(std::string const &p_texte);

#endif // UTILS_H