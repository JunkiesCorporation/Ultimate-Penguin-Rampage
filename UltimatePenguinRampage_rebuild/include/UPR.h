#ifndef UPR_H
#define UPR_H

#include <SDL.h>
#include <string.h>

// La classe principale du programme.
// Contient la fen�tre ainsi que sa surface et son renderer.
// Contient �galement les diverses dimensions constantes utilis�es dans le programme.
class UPR
{
	public:
		static const int LARGEUR_ECRAN = 800; ///< Largeur de l'�cran (= 25 tiles)
		static const int HAUTEUR_ECRAN = 640; ///< Hauteur de l'�cran (= 20 tiles)
		static SDL_Window* fenetre_SDL; ///< La fen�tre du programme
		static SDL_Surface* surface_ecran; ///< La surface de _fenetre_SDL_. Permet d'y afficher du contenu en utilisant le double buffer
	
	protected:
	
	private:
};

#endif // UPR_H