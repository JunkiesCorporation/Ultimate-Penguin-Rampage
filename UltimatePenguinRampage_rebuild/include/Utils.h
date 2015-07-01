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

/** Permet de mesurer le temps écoulé à partir d'un point.
 */
class Timer
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 * Initialise les attributs membres.
		 */
		Timer();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Démarre le Timer.
		 */
		void start();
		
		/** Retourne le nombre de ticks écoulé depuis le démarrage du Timer.
		 * @return Le nombre de ticks.
		 */
		Uint32 getTicks();
		//-----------------------------
	
	protected:
	
	private:
		// Attributs membres privés
		//-----------------------------
		Uint32 m_ticks_depart;
		//-----------------------------
};

#endif