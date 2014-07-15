#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum Direction {
    DIR_BAS,
    DIR_BAS_GAUCHE,
    DIR_GAUCHE,
    DIR_HAUT_GAUCHE,
    DIR_HAUT,
    DIR_HAUT_DROITE,
    DIR_DROITE,
    DIR_BAS_DROITE,
    DIR_IMMOBILE
};

enum TileType {
    TILE_TRAVERSABLE,
    TILE_SOLIDE,
    TILE_OPAQUE // Ce type de tile est idéalement rendu par-dessus le joueur, pour donner un impression de relief
};

#endif // ENUMS_H_INCLUDED
