#ifndef ENTITE_H
#define ENTITE_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <SDL.h>

#include "Carte.h"
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
		 *
		 * @param carte La Carte sur laquelle se situe l'entité.
		 */
		virtual void update(Carte const &carte) = 0;
		
		/** Retourne la hauteur de l'image de l'entité.
		 *
		 * @return La hauteur de #m_image.
		 */
		int getHauteurImage() const;
		
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
		//---------------------------------
	
	protected:
		// Attributs protégés
		//---------------------------------
		/** La direction dans laquelle se déplace l'entité (en radians).
		 *
		 * Comprise entre 0 et 2*Pi radians.
		 */
		double m_direction_deplacement;
		
		/** La direction vers laquelle pointe l'entité (en radians).
		 *
		 * Comprise entre 0 et 2*Pi radians.
		 */
		double m_direction_visee;
		
		/** L'image de l'entité à afficher à l'écran.
		 */
		Texture* m_image;
		
		/** Les Coordonnees de l'entité sur la carte (en px).
		 */
		Coordonnees m_position;
		
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