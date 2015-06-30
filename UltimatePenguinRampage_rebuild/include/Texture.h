#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

/** Classe qui englobe le type SDL_Texture.
 * Classe qui permet de conserver plus d'informations sur les textures chargées dans le jeu.
 *
 * Le chargement et la destructions des textures sont facilités avec les fonctions #charger() et #liberer().
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
		 * \todo Description #charger().
		 *
		 * @param chemin_image Le chemin de l'image BMP à charger.
		 */
		void charger(const char* chemin_image);
		
		/** Libère la Texture.
		 * \todo Description #liberer().
		 */
		void liberer();
		
		/** Affiche la texture à la position donnée.
		 * Attention! Cette fonction ne contient un appel qu'à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
		 *
		 * @param x La position x où afficher l'image.
		 * @param y La position y où afficher l'image.
		 */
		void render(int x, int y) const;
		//-----------------------------
	
	protected:
	
	private:
		// Membres privés
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