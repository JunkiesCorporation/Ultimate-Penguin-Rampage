#ifndef TIMER_H
#define TIMER_H

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

#endif // TIMER_H