#ifndef ARENE_H
#define ARENE_H

#include <string>
#include <SDL.h>
#include <vector>

#include "Projectile.h"
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
		 *
		 * @param chemin_fichier Le chemin d'accès au fichiers d'infos de l'arène.
		 * @param jeu Le jeu en cours.
		 */
		void charger(std::string const &chemin_fichier);
		
		/** Lance l'arène si elle a été précédemment correctement préparée à l'aide de #charger().
		 */
		void lancer();
		
		/** Réinitialise une arène lancée et terminée.
		 *
		 * Permet de réutiliser la même instance d'Arene afin de ne pas encombrer la mémoire en chargeant toutes les arènes du jeu d'un coup.
		 */
		void reinitialiser();
		//---------------------------------
		
		// Fonctions membres publiques et statiques
		//-----------------------------
		/** Ajoute une copie du projectile donné à #m_projectiles_actifs.
		 *
		 * @param p_projectile Le Projectile à ajouter.
		 */
		static void ajouterProjectile(Projectile const &p_projectile);
		//-----------------------------
		
	protected:
		
	private:
		// Fonctions membres privées
		//-----------------------------
		/** Met à jour la position de la caméra.
		 */
		void updateCamera();
		//-----------------------------
		
		// Attributs privés
		//-----------------------------
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
		
		/** Les objets Projectile actifs à l'écran.
		 */
		static std::vector<Projectile> m_projectiles_actifs;
		
		/** Compteur du nombre de ticks nécessaires à l'affichage d'une trame à l'écran.
		 * 
		 * Utilisé de paire avec le #timer.
		 */
		int m_ticks_image;
		
		/** Le Timer utilisé par diverses fonctions afin de maintenir les FPS aux alentours de 60.
		 */
		Timer m_timer;
		//-----------------------------
	
};

#endif // ARENE_H