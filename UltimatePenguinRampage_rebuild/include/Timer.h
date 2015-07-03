#ifndef TIMER_H
#define TIMER_H

/** Classe permettant de mesurer le temps écoulé à partir d'un point.
 */
class Timer
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
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
		 *
		 * @return Le nombre de ticks écoulé depuis l'appel de #start().
		 */
		Uint32 getTicks();
		//-----------------------------
	
	protected:
	
	private:
		// Attributs privés
		//-----------------------------
		/** Le nombre de ticks écoulés au moment de l'appel à #start().
		 */
		Uint32 m_ticks_depart;
		//-----------------------------
};

#endif // TIMER_H