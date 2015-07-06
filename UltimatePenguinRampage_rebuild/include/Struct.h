#ifndef STRUCT_H
#define STRUCT_H

#include <SDL.h>

#include "Enums.h"

/** Petite structure pour contenir des positions avec 2 coordonnées.
 */
struct Position
{
	/** La coordonnée x de la position.
	 */
	int x;
	
	/** La coordonnée y de la position.
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