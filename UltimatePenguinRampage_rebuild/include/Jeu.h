#ifndef JEU_H
#define JEU_H

#include <SDL.h>
#include <vector>

#include "Arme.h"
#include "Profil.h"
#include "Arene.h"
#include "Texture.h"
#include "Timer.h"

/** Classe permettant le déroulement du jeu au-delà de menu principal.
 *
 * Permet la navigation pour atteindre et lancer les différentes fonctionnalités du jeu (mode histoire, mode arène, etc.) et la visualisations des informations du Profil du joueur.
 */
class Jeu
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs du Jeu avec des valeurs par défaut.
		 */
		Jeu();
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 * 
		 * Suppression d'éventuelles textures oubliées et fermeture de leur pointeur respectif.
		 */
		~Jeu();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Retourne l'arme dont l'id correspond à celui donné en paramètre.
		 * 
		 * @param p_id L'id de l'arme à retourner.
		 *
		 * @return L'arme de #m_liste_armes correspondant à l'id donné.
		 */
		Arme getArmeDepuisID(int const &p_id) const;
		
		/** Affiche l'écran principal du jeu et permet la navigation vers les fonctionnalités du jeu.
		 *
		 * @param profil_joueur Le profil utilisé par le joueur.
		 */
		void lancer(Profil* profil_joueur);
		//-----------------------------
	
	protected:
	
	private:
		// Types privés
		//-----------------------------
		/** Les différentes options de l'écran principal du jeu.
		 */
		enum EnumOptionsEcranPrincipal
		{
			/** Le mode histoire. */
			MODE_HISTOIRE,
			/** Le mode arène. */
			MODE_ARENE,
			/** Option de retour vers le menu principal. */
			RETOUR_MENU,
			/** Permet l'initialisation de tableaux avec une taille suffisante. */
			NB_OPTIONS
		};
		//-----------------------------
		
		// Fonctions membres privées
		//-----------------------------
		/** Charge les textures nécessaires à l'écran principal du jeu.
		 *
		 * Initialise les textures suivantes :
		 * - #m_texture_fond_jeu
		 * - #m_textures_options_ecran_jeu
		 */
		void chargerTexturesEcran();
		
		/** Charge les textures nécessaires à l'écran du mode histoire.
		 *
		 * Initialise les textures suivantes :
		 * - m_texture_fond_mode_histoire
		 */
		void chargerTexturesModeHistoire();
		
		/** Libère les textures de l'écran principal du jeu.
		 */
		void libererTexturesEcran();
		
		/** Libère les textures de l'écran du mode histoire.
		 */
		void libererTexturesModeHistoire();
		
		/** Affiche et gère le mode histoire.
		 *
		 * - Récupère le profil du joueur donné lors du lancement du jeu.
		 * - Affiche la sélection des différents niveau de l'histoire.
		 * - Lance le niveau choisi par l'utilisateur.
		 *
		 * @param profil_joueur Le Profil du joueur en cours d'utilisation.
		 */
		void modeHistoire(Profil* profil_joueur);
		//-----------------------------
		
		// Attributs privés
		//-----------------------------
		/** L'instance d'Arene à charger lorsque le joueur lance un niveau.
		 */
		Arene m_arene;
		
		/** Objet permettant la manipulation des événements au sein des diverses boucles.
		 */
		SDL_Event e;
		
		/** Liste d'objets Arme contenant les exemplaires par défaut de chaque arme du jeu.
		 */
		std::vector<Arme> m_liste_armes;
		
		/** L'image du cadre de sélection.
		 */
		Texture* m_texture_cadre_selection;
		
		/** L'image de fond de l'écran principal du jeu.
		 */
		Texture* m_texture_fond_jeu;
		
		/** L'image de fond de l'écran du mode histoire.
		 */
		Texture* m_texture_fond_mode_histoire;
		
		/** Les images des options de l'écran principal du jeu.
		 */
		Texture* m_textures_options_ecran_jeu[NB_OPTIONS];
		
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

#endif // JEU_H