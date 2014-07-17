#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Tileset.h"
#include "Utils.h"
#include "Enums.h"

Tileset::Tileset() : m_largeur(0), m_hauteur(0), m_largeurTiles(0), m_hauteurTiles(0), m_tiles(NULL)
{
    std::cout << "Tileset construit (sans param)" << std::endl;
}

Tileset::Tileset(std::string cheminFichier) : m_largeur(0), m_hauteur(0), m_largeurTiles(0), m_hauteurTiles(0), m_tiles(NULL)
{
    charger(cheminFichier);
    std::cout << "Tileset construit (avec param)" << std::endl;
}

Tileset::~Tileset()
{
    delete m_tiles; m_tiles = NULL;
    m_image.liberer();
    std::cout << "Tileset detruit" << std::endl;
}

void Tileset::charger(std::string cheminFichier) {
    std::ifstream fichier(cheminFichier.c_str());
    std::string ligne("");

    if(!fichier) {
        std::cout << "Erreur : Echec du chargement de : " << cheminFichier << std::endl;
    } else {
        // Lecture du [header]
        fichier >> ligne; if(ligne != "[header]") {
            std::cout << "Erreur : [header] manquant dans " << cheminFichier << std::endl;
        }
        fichier >> ligne; fichier >> ligne; m_largeur = atoi(ligne.c_str()); // Lecture de la largeur
        fichier >> ligne; fichier >> ligne; m_hauteur = atoi(ligne.c_str()); // Lecture de la hauteur
        fichier >> ligne; fichier >> ligne; m_largeurTiles = atoi(ligne.c_str()); // Lecture de la largeur d'une tile
        fichier >> ligne; fichier >> ligne; m_hauteurTiles = atoi(ligne.c_str()); // Lecture de la hauteur d'une tile
        fichier >> ligne; fichier >> ligne; (&m_image)->~Texture(); new (&m_image) Texture(ligne); // Chargement de l'image

        // Initialisation des tiles
        m_tiles = new Tile[m_largeur * m_hauteur];
        int tileID(0);
        for(int y(0); y < m_hauteur; y++) {
            for(int x(0); x < m_largeur; x++) {
                tileID = x + y*10 + 1;
                m_tiles[tileID-1].tileID = tileID;
                m_tiles[tileID-1].clipQuad.x = x * m_largeurTiles;
                m_tiles[tileID-1].clipQuad.y = y * m_hauteurTiles;
                m_tiles[tileID-1].clipQuad.w = m_largeurTiles;
                m_tiles[tileID-1].clipQuad.h = m_hauteurTiles;
                m_tiles[tileID-1].type = TILE_TRAVERSABLE;
            }
        }

        fichier >> ligne; if(ligne != "[tiles_solides]") {
            std::cout << "Erreur : [tiles_solides] manquant dans " << cheminFichier << std::endl;
        }
        int nombreTileSolides(0);
        fichier >> ligne; fichier >> ligne; nombreTileSolides = atoi(ligne.c_str());
        for(int i(0); i < nombreTileSolides; i++) {
            fichier >> ligne;
            m_tiles[atoi(ligne.c_str()) - 1].type = TILE_SOLIDE;
        }

        // TODO Charger [tiles_opaques]

    }
}

void Tileset::render(int tileID, int x, int y)  const {
    SDL_Rect renderQuad = {x*m_largeurTiles, y*m_hauteurTiles, m_largeurTiles, m_hauteurTiles};
    SDL_RenderCopy(Utils::renderer, m_image.getImage(), &m_tiles[tileID-1].clipQuad, &renderQuad);
}

bool Tileset::isTileSolide(int tileID) const {
    return m_tiles[tileID-1].type == TILE_SOLIDE;
}
