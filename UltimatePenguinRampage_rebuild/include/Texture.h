#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

#include "Struct.h"

/** Classe qui englobe le type SDL_Texture.
 * Classe qui permet de conserver plus d'informations sur les textures chargées dans le jeu.
 *
 * Le chargement et la destruction des textures sont facilités avec les fonctions #charger() et #liberer().
 */
class Texture
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 * Initialise #m_image à NULL ainsi que #m_largeur et #m_hauteur à 0.
		 */
		Texture();
		
		/** Constructeur avec chemin d'image.
		 * Fait appel à la fonction #charger(const char*) afin de charger l'image dans #m_image et de régler #m_largeur et #m_hauteur.
		 *
		 * @param chemin_image Le chemin de l'image BMP à charger.
		 */
		Texture(const char* chemin_image);
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur.
		 * Détruit la Texture proprement en libérant #m_image.
		 */
		~Texture();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Charge l'image située au chemin donné.
		 * Créée une nouvelle SDL_Texture avec l'image donnée. Récupère également la largeur et la hauteur de l'image.
		 *
		 * Sert également à donnée une nouvelle image à une Texture déjà utilisée.
		 *
		 * @param chemin_image Le chemin de l'image BMP à charger.
		 */
		void charger(const char* chemin_image);
		
		/** Libère la Texture.
		 * Libère la SDL_Texture grâce à SDL_DestroyTexture() et ré-initialise les attributs membres.
		 *
		 * Doit être appelée lorsque l'usage de la Texture est terminée ou lorsque l'on souhaite la réutiliser.
		 *
		 * Appelée par défaut par #~Texture().		 
		 */
		void liberer();
		
		/** Affiche la texture aux coordonnées données.
		 * Attention! Cette fonction ne contient un appel qu'à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
		 *
		 * @param x La position x où afficher l'image.
		 * @param y La position y où afficher l'image.
		 */
		void render(int x, int y) const;
		
		/** Affiche la texture à la Position donnée.
		 * Attention! Cette fonction ne contient un appel qu'à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
		 *
		 * @param pos La Position où afficher l'image.
		 */
		void render(Position pos) const;
		
		/** Retourne le nombre de textures restantes dans la mémoire.
		 *
		 * @return #m_nombre_textures_restantes Le nombre de textures restantes.
		 */
		static int getTexturesRestantes();
		
		/** Retourne la largeur de l'image contenue.
		 * @return #m_largeur La largeur de l'image.
		 */
		int getLargeur() const;
		
		/** Retourne la hauteur de l'image contenue.
		 * @return #m_hauteur La hauteur de l'image.
		 */
		int getHauteur() const;
		//-----------------------------
		
		// Attributs membres publiques et static
		//-----------------------------
		static int m_nombre_textures_restantes;
		//-----------------------------
	
	protected:
	
	private:		
		// Attributs membres privés
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