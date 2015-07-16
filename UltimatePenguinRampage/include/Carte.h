#ifndef CARTE_H
#define CARTE_H

#include <SDL.h>
#include <string>

#include "Tileset.h"
#include "Struct.h"

/** Classe contenant toutes les informations sur la carte d'une arène.
 */
class Carte
{
	public:
	// Constructeurs
	//---------------------------------
	/** Constructeur par défaut.
	 * 
	 * Initialise les attributs à des valeurs par défaut.
	 */
	Carte();
	//---------------------------------
	
	// Destructeur
	//---------------------------------
	/** Destructeur par défaut.
	 */
	~Carte();
	//---------------------------------
	
	// Fonctions membres publiques
	//---------------------------------
	/** Lis le fichier associé à la carte et charge les informations.
	 *
	 * @param chemin_fichier Le chemin du fichier à charger.
	 *
	 * @return Si le chargement de la carte à réussi.
	 */
	bool charger(std::string chemin_fichier);
	
	/** Réinitialise la carte.
	 *
	 * Réinitialise les éléments modifiés par #charger() en vue d'une réutilisation de l'instance de Carte.
	 */
	void reinitialiser();
	
	/** Affiche les tiles de la carte qui se trouvent sous la caméra.
	 *
	 * Attention! Cette fonction ne contient qu'un appel à SDL_RenderCopy(), il faut tout de même appeler SDL_RenderPresent() après.
	 *
	 * @param camera La caméra du niveau.
	 */
	void render(SDL_Rect camera) const;
	
	/** Retourne si la tile à la position indiquée est solide ou non.
	 *
	 * @return Si la tile indiquée est solide.
	 */
	bool isTileSolide(int x, int y) const;
	
	/** Retourne la hauteur de la carte (en tiles).
	 *
	 * @return #m_hauteur La hauteur de la carte.
	 */
	int getHauteur() const;
	
	/** Retourne la hauteur d'une tile sur la carte.
	 *
	 * @return La hauteur d'une tile de m_tileset.
	 */
	int getHauteurTile() const;
	
	/** Retourne la largeur de la carte (en tiles).
	 *
	 * @return #m_largeur La largeur de la carte.
	 */
	int getLargeur() const;
	
	/** Retourne la largeur d'une tile sur la carte.
	 *
	 * @return La largeur d'une tile de m_tileset.
	 */
	int getLargeurTile() const;
	
	/** Retourne la position de départ du joueur (en px).
	 *
	 * @return m_depart_joueur Les coordonnées de départ du joueur.
	 */
	Coordonnees getPositionDepartJoueur() const;
	//---------------------------------
	
	protected:
	
	private:
	// Fonctions membres privées
	//---------------------------------
	//---------------------------------
	
	// Attributs privés
	//---------------------------------
	/** Les Coordonnees de départ du joueur (en tiles).
	 */
	Coordonnees m_depart_joueur;
	
	/** La hauteur de la carte (en tiles).
	 */
	int m_hauteur;
	
	/** Grille contenant les ID des tiles à afficher.
	 */
	int** m_id_tiles;
	
	/** La largeur de la carte (en tiles).
	 */
	int m_largeur;
	
	/** Le Tileset utilisé par la carte.
	 */
	Tileset m_tileset;
	//---------------------------------
	
};

#endif // CARTE_H