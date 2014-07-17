#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct Pos {
    int x;
    int y;
};

struct Tile {
    int tileID;
    SDL_Rect clipQuad;
    TileType type;
};

#endif // STRUCT_H_INCLUDED
