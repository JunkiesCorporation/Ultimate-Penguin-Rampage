#ifndef JOUEUR_H
#define JOUEUR_H

#include "Entite.h"

class Joueur : public Entite
{
	public:
		// Constructeurs
		//---------------------------------
		/** Constructeur par défaut.
		 * 
		 * Appel Entite::Entite().
		 *
		 * Initialise les attributs à des valeurs pas défaut.
		 */
		Joueur();
		
		/** Constructeur avec position de départ.
		 *
		 * @param pos_depart La position de départ de l'entité.
		 */
		Joueur(Coordonnees pos_depart);
		//---------------------------------
		
		// Destructeur
		//---------------------------------
		/** Destructeur par défaut.
		 *
		 * Appel Entite::~Entite().
		 *
		 * Supprime les attributs non nuls.
		 */
		~Joueur();
		//---------------------------------
		
		// Fonctions membres publiques
		//---------------------------------
		/** Gère les événements s'ils s'appliquent au Joueur.
		 *
		 * @param e L'événement à gérer.
		 * @param camera La caméra de l'arène
		 */
		void gererEvenement(SDL_Event const &e, SDL_Rect const &camera);
		
		/** Met à jour le joueur.
		 *
		 * @sa Entite::update().
		 */
		void update();
		//---------------------------------
	
	protected:
	
	private:
		// Types privés
		//---------------------------------
		/** Mot-clef permettant l'accès rapide aux méthodes d'Entite.
		 */
		typedef Entite super;
		
		/** Les actions possibles du joueur.
		 */
		enum EnumActions
		{
			/** Le joueur avance dans la direction actuelle.
			 */
			AVANCER,
			/** La souris est déplacée et le joueur change de direction.
			 */
			CHANGE_DIRECTION,
			/** Translation vers la gauche de la direction.
			 */
			PAN_GAUCHE,
			/** Translation vers la droite de la direction.
			 */
			PAN_DROITE,
			/** Permet l'initialisation de tableaux avec une taille suffisante. 
			 */
			NB_ACTIONS
		};
		
		/** Les 8 découpages de la direction.
		 */
		enum EnumDirections
		{
			
			HAUT,
			HAUT_DROITE,
			DROITE,
			BAS_DROITE,
			BAS,
			BAS_GAUCHE,
			GAUCHE,
			HAUT_GAUCHE,
			NB_DIRECTIONS
		};
		//---------------------------------
		
		// Attributs privés
		//---------------------------------
		/** Tableau pour stocker les actions en cours du joueur.
		 */
		bool m_actions[NB_ACTIONS];
		
		/** Tableau contenant les 8 différentes images du joueur.
		 */
		Texture* m_textures[NB_DIRECTIONS];
		//---------------------------------
	
};

#endif // JOUEUR_H