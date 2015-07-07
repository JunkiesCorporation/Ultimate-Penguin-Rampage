#ifndef TILESET_H
#define TILESET_H

#include <string>

#include "Struct.h"
#include "Texture.h"

/** Objet contenant un tileset précis et permettant son affichage à l'écran grâce aux numéros d'ID de ses tiles.
 */
class Tileset
{
	public:
	// Constructeurs
	//---------------------------------
	/** Constructeur par défaut.
	 *
	 * Initialise les attributs à des valeurs par défaut.
	 */
	Tileset();
	//---------------------------------
	
	// Destructeur
	//---------------------------------
	/** Destructeur par défaut.
	 */
	~Tileset();
	//---------------------------------
	
	// Fonctions membres publiques
	//---------------------------------
	/** Lis le fichier donné associé au Tileset et charge les informations.
	 *
	 * @param chemin_fichier Le chemin du fichier à charger.
	 *
	 * @return Si le chargement du Tileset à réussi.
	 */
	bool charger(std::string chemin_fichier);
	
	/** Réinitialise le Tileset.
	 *
	 * Réinitialise les éléments modifiés par #charger() en vue d'une réutilisation de l'instance de Tileset.
	 */
	void reinitialiser();
	
	/** Affiche la tile donnée aux coordonnées indiquées.
	 *
	 * Attention! Cette fonction ne contient qu'un appel à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
	 *
	 * @param id_tile L'ID de la tile à afficher.
	 * @param x La coordonnée x où afficher la tile.
	 * @param y La coordonnée y où afficher la tile.
	 */
	void render(int id_tile, int x, int y) const;
	
	/** Retourne la largeur d'une tile du tileset.
	 *
	 * @return #m_largeur_tile La largeur d'une tile.
	 */
	int getLargeurTile() const;
	
	/** Retourne la hauteur d'une tile du tileset.
	 *
	 * @return #m_hauteur_tile La hauteur d'une tile.
	 */
	int getHauteurTile() const;
	//---------------------------------
	
	protected:
	
	private:
	// Attributs privés
	//---------------------------------
	/** La hauteur du tileset (en tiles).
	 */
	int m_hauteur;
	
	/** La hauteur d'une tile du tileset (en px).
	 */
	int m_hauteur_tile;
	
	/** L'image contenant les tiles du tileset.
	 */
	Texture *m_image;
	
	/** La largeur du tileset (en tiles).
	 */
	int m_largeur;
	
	/** La largeur d'une tile du tileset (en px).
	 */
	int m_largeur_tile;
	
	/** Le tableau de tiles du tileset.
	 */
	Tile* m_tiles;
	//---------------------------------
	
};

#endif // TILESET_H