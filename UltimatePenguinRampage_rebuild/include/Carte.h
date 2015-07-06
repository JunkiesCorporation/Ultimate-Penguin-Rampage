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
	//---------------------------------
	
	protected:
	
	private:
	// Fonctions membres privées
	//---------------------------------
	//---------------------------------
	
	// Attributs privés
	//---------------------------------
	/** La Position de départ du joueur.
	 */
	Position m_depart_joueur;
	
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