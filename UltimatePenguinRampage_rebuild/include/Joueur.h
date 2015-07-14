#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <SDL.h>

#include "Entite.h"
#include "Struct.h"
#include "Carte.h"
#include "Arme.h"
#include "Texture.h"

class Jeu;

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
		
		/** Constructeur de chargement.
		 *
		 * @param id_armes_depart Vecteur des id des armes de départ du joueur.
		 * @param jeu Le jeu en cours
		 * @param pos_depart La position de départ de l'entité.
		 */
		Joueur(std::vector<int> const &id_armes_depart, Jeu const &jeu, Coordonnees pos_depart);
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
		 * @param carte La carte sur laquelle le joueur joue.
		 * @sa Entite::update().
		 */
		void update(Carte const &carte);
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
			/** La souris est déplacée et le joueur change de direction.
			 */
			CHANGE_DIRECTION,
			/** Le joueur se dirige vers le bas.*
			 */
			DIR_BAS,
			/** Le joueur se dirige vers la droite.*
			 */
			DIR_DROITE,
			/** Le joueur se dirige vers la gauche.*
			 */
			DIR_GAUCHE,
			/** Le joueur se dirige vers le haut.*
			 */
			DIR_HAUT,
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
		
		/** Les armes que le joueur porte sur lui pendant la partie.
		 */
		std::vector<Arme> m_armes_portees;
		
		/** Pointeur vers l'arme sélectionnée.
		 */
		Arme* m_arme_selectionnee;
		
		/** L'indice dans #m_armes_portees de l'arme en cours d'utilisation.
		 */
		int m_num_arme_selectionnee;
		
		/** Tableau contenant les 8 différentes images du joueur.
		 */
		Texture* m_textures[NB_DIRECTIONS];
		//---------------------------------
	
};

#endif // JOUEUR_H