#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

#include "Struct.h"

/** Classe qui englobe le type SDL_Texture.
 * Permet de conserver plus d'informations sur les textures chargées dans le jeu.
 *
 * Le chargement et la destruction des textures sont facilités avec les fonctions #charger(const char*) et #liberer().
 */
class Texture
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs à des valeurs par défaut.
		 */
		Texture();
		
		/** Constructeur avec chemin d'image BMP.
		 *
		 * Fait appel à la fonction #charger(const char*) afin de charger l'image dans #m_image et de régler #m_largeur et #m_hauteur.
		 *
		 * @param chemin_image Le chemin de l'image BMP à charger.
		 */
		Texture(const char* chemin_image);
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 *
		 * Détruit la Texture proprement en libérant #m_image grâce à #liberer().
		 */
		~Texture();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Charge l'image située au chemin donné.
		 *
		 * - Créé une nouvelle SDL_Texture avec l'image donnée. Récupère également la largeur et la hauteur de l'image.
		 * - Sert également à donner une nouvelle image à une Texture déjà utilisée.
		 *
		 * En cas d'erreur : affiche un message dans la console et laisse le pointeur #m_image initialisé à NULL.
		 *
		 * @param chemin_image Le chemin de l'image BMP à charger.
		 */
		void charger(const char* chemin_image);
		
		/** Libère la Texture.
		 *
		 * Libère la SDL_Texture grâce à SDL_DestroyTexture() et ré-initialise les attributs membres.
		 *
		 * Doit être appelée lorsque l'usage de la Texture est terminée ou lorsque l'on souhaite la réutiliser.
		 *
		 * Appelée par défaut par #~Texture().		 
		 */
		void liberer();
		
		/** Affiche la texture aux coordonnées données.
		 *
		 * __Attention!__ Cette fonction ne contient qu'un appel à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
		 *
		 * @param x La position x où afficher l'image.
		 * @param y La position y où afficher l'image.
		 */
		void render(int x, int y) const;
		
		/** Affiche la texture à la Position donnée.
		 *
		 * Attention! Cette fonction ne contient qu'un appel à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
		 *
		 * @param pos_render La Position où afficher l'image.
		 */
		void render(Position pos_render) const;
		
		/** Retourne la largeur de l'image contenue.
		 *
		 * @return #m_largeur La largeur de l'image.
		 */
		int getLargeur() const;
		
		/** Retourne la hauteur de l'image contenue.
		 *
		 * @return #m_hauteur La hauteur de l'image.
		 */
		int getHauteur() const;
		//-----------------------------
		
		// Fonctions membres publiques statiques
		//-----------------------------
		/** Retourne le nombre de textures restantes dans la mémoire.
		 *
		 * @return #m_nombre_textures_restantes Le nombre de textures restantes.
		 */
		static int getTexturesRestantes();
		//-----------------------------
		
		// Attributs publics et statiques
		//-----------------------------
		/** Le nombre de textures restantes en mémoire.
		 */
		static int m_nombre_textures_restantes;
		//-----------------------------
	
	protected:
	
	private:		
		// Attributs privés
		//-----------------------------
		/** L'image contenue dans la texture.
		 */
		SDL_Texture* m_image;
		
		/** La largeur (en px) de l'image chargée.
		 */
		int m_largeur;
		
		/** La hauteur (en px) de l'image chargée.
		 */
		int m_hauteur;
		//-----------------------------
};

#endif // TEXTURE_H