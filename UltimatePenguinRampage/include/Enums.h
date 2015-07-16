#ifndef ENUMS_H
#define ENUMS_H

/** Les différents types de tiles possible sur une carte.
 */
enum TileType
{
	TILE_TRAVERSABLE,
	TILE_SOLIDE
};

/** Les différents types d'armes possibles dans le jeu.
 */
enum TypeArme
{
	/** Une arme de corps à corps.
	 */
	ARME_CORPS_A_CORPS,
	/** Une arme de jet avec projectile.
	 */
	ARME_DE_JET,
	NB_TYPES_ARMES
};

/** Tableau contenant les différents noms de types d'armes.
 *
 * Il permet de reconnaître le type d'arme à la lecture du fichier. Il doit être mis à jour en même temps que l'Enum TypeArme et ses éléments doivent être listés dans le même ordre.
 */
const std::string type_armes_string[NB_TYPES_ARMES] = {
	"arme_corps_a_corps",
	"arme_de_jet"
	};

#endif // ENUMS_H