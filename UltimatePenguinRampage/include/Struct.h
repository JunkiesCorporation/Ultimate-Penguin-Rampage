#ifndef STRUCT_H
#define STRUCT_H

#include <SDL.h>

#include "Enums.h"

/** Petite structure pour contenir des coordonnées en deux dimensions.
 */
struct Coordonnees
{
	/** La coordonnée x.
	 */
	int x;
	
	/** La coordonnée y.
	 */
	int y;
};

/** Structure pour contenir les informations essentielles des tiles, éléments composant toutes les cartes du jeu.
 */
struct Tile
{
	/** Le numéro d'identification de la tile, relatif à son tileset.
	 */
	int id_tile;
	
	/** Le rectangle pour découper la tile de son tileset.
	 */
	SDL_Rect rect_clip;
	
	/** Le type de la tile.
	 */
	TileType type;
};

#endif // STRUCT_H