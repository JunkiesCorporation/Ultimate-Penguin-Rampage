#ifndef CARTE_H
#define CARTE_H

#include <string>

#include "Struct.h"

/** Classe contenant toutes les informations sur la carte d'une arène.
 */
class Carte
{
	public:
	// Constructeurs
	//---------------------------------
	/** Constructeur par défaut.
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
	Tilset m_tileset;
	//---------------------------------
	
};

#endif // CARTE_H