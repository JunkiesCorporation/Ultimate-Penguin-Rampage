#ifndef UTILS_H
#define UTILS_H

/** Regroupe quelques fonctions d'utilité générale.
 */
class Utils
{
	public:
		// Fonctions membres publiques
		//-----------------------------
		/** Initialise la SDL et ses principaux composants.
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

#endif // UTILS_H