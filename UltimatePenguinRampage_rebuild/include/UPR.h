#ifndef UPR_H
#define UPR_H

#include <SDL.h>

/** La classe principale du programme.
 * Contient la fenêtre ainsi que sa surface et son renderer.
 * Contient également les diverses dimensions constantes utilisées dans le programme.
 */
class UPR
{
	public:
		// Attributs membres publiques
		//-----------------------------
		/** Largeur de l'écran (= 25 tiles).
		 */
		static const int LARGEUR_ECRAN = 800;
		
		/** Hauteur de l'écran (= 20 tiles).
		 */
		static const int HAUTEUR_ECRAN = 640;
		
		/** La fenêtre du programme.
		 * 
		 * Créée dans Utils::initialisationSDL().
		 *
		 * Détruite dans Utils::quitter().
		 */
		static SDL_Window* fenetre_SDL; 
		
		/** Le renderer de UPR::fenetre_SDL.
		 * 
		 * Créé dans Utils::initialisationSDL().
		 * 
		 * Détruit dans Utils::quitter();
		 */
		static SDL_Renderer* renderer_SDL;
		//-----------------------------
	
	protected:
	
	private:
};

//--------------------------
// Prototypes des fonctions
//--------------------------

/** Gère l'affichage et le contrôle du menu principal.
 * @return Le numéro de l'option choisie.
 */
int gestionMenuPrincipal();

#endif // UPR_H