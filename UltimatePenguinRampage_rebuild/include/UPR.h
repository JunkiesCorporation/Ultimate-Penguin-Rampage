#ifndef UPR_H
#define UPR_H

#include <SDL.h>
#include <string.h>

/** La classe principale du programme.
 * Contient la fenêtre ainsi que sa surface et son renderer.
 * Contient également les diverses dimensions constantes utilisées dans le programme.
 */
class UPR
{
	public:
		/** Largeur de l'écran (= 25 tiles).
		 */
		static const int LARGEUR_ECRAN = 800;
		
		/** Hauteur de l'écran (= 20 tiles).
		 */
		static const int HAUTEUR_ECRAN = 640;
		
		/** La fenêtre du programme.
		 * 
		 * Créée par Utils::initialisationSDL().
		 *
		 * Détruite par SDL_DestroyWindow() dans Utils::quitter().
		 */
		static SDL_Window* fenetre_SDL; 
		
		/** La surface contenue par UPR::fenetre_SDL. 
		 * 
		 * Permet d'y afficher du contenu en utilisant le double buffer.
		 *
		 * Initialisée dans Utils::initialisationSDL().
		 * 
		 * Elle n'a pas d'instructions de suppression explicites, elle est détruite par la fonction SDL_DestroyWindow() utilisée dans la fonction Utils::quitter().
		 */
		static SDL_Surface* surface_ecran;
	
	protected:
	
	private:
};

#endif // UPR_H