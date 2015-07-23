#ifndef ENTITE_H
#define ENTITE_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <SDL.h>

#include "Carte.h"
#include "Enums.h"
#include "Struct.h"
#include "Texture.h"

#define M_PI_8 M_PI_4 / 2.

/** Classe abstraite qui regroupe toutes les fonctionnalités communes aux entités qui apparaissent dans une arène.
 */
class Entite
{
	public:
		// Constructeurs
		//---------------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs à des valeurs par défaut.
		 */
		Entite();
		
		/** Constructeur avec position de départ.
		 *
		 * Appel Entite::Entite(Coordonnees).
		 *
		 * Initialise l'image du Joueur.
		 *
		 * @param pos_depart La position de départ de l'entité.
		 */
		Entite(Coordonnees pos_depart);
		
		/** Constructeur de copie.
		 *
		 * Permet de créer une nouvelle instance d'Entite identique à celle donnée en paramètre sauf pour l'image qui n'est pas copié et doit être allouée après.
		 *
		 * @param entite L'entité à copier.
		 */
		Entite(Entite const &entite);
		//---------------------------------
		
		// Destructeur
		//---------------------------------
		/** Destructeur par défaut.
		 *
		 * Il est virtuel car une classe abstraite ne peut avoir de destructeur.
		 */
		virtual ~Entite();
		//---------------------------------
		
		// Fonctions membres publiques
		//---------------------------------
		/** Affiche l'image de l'entité si elle est sous la caméra.
		 *
		 * @param camera La caméra du niveau.
		 */
		void render(SDL_Rect const &camera);
		
		/** Met à jour l'entité.
		 *
		 * Toutes les actions que l'entité effectue au cours du niveau partent de cette fonction.
		 * Entite::update() met à jour la position en fonction de la vitesse et de la direction de déplacement si l'entité est en mouvement. Elle doit être appelée explicitement par les classes filles.
		 *
		 * @param carte La Carte sur laquelle se situe l'entité.
		 */
		virtual void update(Carte const &carte);
		
		
		/** Retourne la direction de déplacement de l'entité (en radians).
		 *
		 * @return #m_direction_deplacement La direction de déplacement de l'entité.
		 */
		double getDirectionDeplacement() const;
		
		/** Retourne la direction de visée de l'entité (en radians).
		 *
		 * @return #m_direction_visee La direction de visée de l'entité.
		 */
		double getDirectionVisee() const;
		
		/** Retourne la hauteur de l'image de l'entité.
		 *
		 * @return La hauteur de #m_image.
		 */
		int getHauteurImage() const;
		
		/** Retourne le pointeur vers l'image de l'entité.
		 *
		 * @return #m_image L'image de l'entité.
		 */
		Texture* getImage() const;
		
		/** Retourne la largeur de l'image de l'entité.
		 *
		 * @return La largeur de #m_image.
		 */
		int getLargeurImage() const;
		
		/** Retourne la position de l'entité.
		 *
		 * @return #m_position.
		 */
		Coordonnees getPosition() const;
		
		/** Retourne la structure qui contient les composantes de la vitesse de l'entité.
		 *
		 * @return #m_vitesse La vitesse de l'entité.
		 */
		Coordonnees getVitesse() const;
		
		/** Retourne la vitesse maximum de l'entité.
		 *
		 * @return #m_vitesse_max La vitesse maximum de l'entité.
		 */
		int getVitesseMax() const;
		
		/** Si l'entité est en mouvement.
		 *
		 * @return #m_se_deplace Si l'entité se déplace.
		 */
		bool seDeplace() const;
		
		/** Permet de modifier la direction de déplacement de l'entité.
		 *
		 * @param p_direction_deplacement La nouvelle direction de déplacement de l'entité.
		 */
		void setDirectionDeplacement(double p_direction_deplacement);
		
		/** Permet de modifier la position de l'entité.
		 *
		 * @param p_position La nouvelle position de l'entité.
		 */
		void setPosition(Coordonnees p_position);
		//---------------------------------
	
	protected:
		// Attributs protégés
		//---------------------------------
		/** La direction dans laquelle se déplace l'entité (en radians).
		 *
		 * Comprise entre 0 et 2*Pi radians.
		 */
		double m_angle_deplacement;
		
		/** La direction vers laquelle pointe l'entité (en radians).
		 *
		 * Comprise entre 0 et 2*Pi radians.
		 */
		double m_angle_visee;
		
		/** L'image de l'entité à afficher à l'écran.
		 */
		Texture* m_image;
		
		/** Les Coordonnees de l'entité sur la carte (en px).
		 */
		Coordonnees m_position;
		
		/** Si l'entité est en train de se déplacer.
		 */
		bool m_se_deplace;
		
		/** Les composantes de la vitesse de l'entité.
		 */
		Coordonnees m_vitesse;
		
		/** La vitesse maximum de l'entité.
		 */
		int m_vitesse_max;
		//---------------------------------
	
	private:
	
};

#endif // ENTITE_H