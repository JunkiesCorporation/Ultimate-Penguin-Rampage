#ifndef ARENE_H
#define ARENE_H

#include "Carte.h"
#include "Joueur.h"
#include "Timer.h"

/** Objet permettant le contrôle d'un niveau jouable.
 */ 
class Arene
{
	public:
		// Constructeurs
		//---------------------------------
		/** Constructeur par défaut.
		 * 
		 * Initialise les attributs à des valeurs par défaut.
		 */
		Arene();
		//---------------------------------
		
		// Destructeur
		//---------------------------------
		/** Destructeur par défaut.
		 */
		~Arene();
		//---------------------------------
		
		// Fonctions membres publiques
		//---------------------------------
		/** Charge les éléments requis pour le fonctionnement de cette instance d'Arene.
		 */
		void charger();
		
		/** Lance l'arène si elle a été précédemment correctement préparée à l'aide de #charger().
		 */
		void lancer();
		
		/** Réinitialise une arène lancée et terminée.
		 *
		 * Permet de réutiliser la même instance d'Arene afin de ne pas encombrer la mémoire en chargeant toutes les arènes du jeu d'un coup.
		 */
		void reinitialiser();
		//---------------------------------
		
	protected:
		
	private:
		// Fonctions membres privées
		//-----------------------------
		/** Met à jour la position de la caméra.
		 */
		void updateCamera();
		//-----------------------------
		
		// Attributs privés
		//---------------------------------
		/** La caméra qui permet l'affichage.
		 *
		 * Schématiquement c'est un rectangle que l'on déplace au-dessus de la carte. Le personnage reste toujours au centre.
		 */
		SDL_Rect m_camera;
		
		/** La carte de l'arène.
		 */
		Carte m_carte;
		
		/** Si cette instance d'Arene est prête à être lancée.
		 */
		bool m_est_prete;
		
		/** L'objet joueur contrôlé par l'utilisateur.
		 */
		Joueur* m_joueur;
		
		/** Compteur du nombre de ticks nécessaires à l'affichage d'une trame à l'écran.
		 * 
		 * Utilisé de paire avec le #timer.
		 */
		int m_ticks_image;
		
		/** Le Timer utilisé par diverses fonctions afin de maintenir les FPS aux alentours de 60.
		 */
		Timer m_timer;
	//---------------------------------
	
};

#endif // ARENE_H