#ifndef CARTE_H
#define CARTE_H

/** Classe contenant toutes les informations sur la carte d'une arène.
 */
class Carte
{
	public:
	// Constructeurs
	//---------------------------------
	/** Constructeur avec chemin d'accès au fichier contenant les données de la carte.
	 * 
	 * @param chemin_fichier Le chemin du fichier à charger.
	 */
	Carte(std::string chemin_fichier);
	//---------------------------------
	
	// Destructeur
	//---------------------------------
	/** Destructeur par défaut.
	 */
	~Carte();
	//---------------------------------
	
	// Fonctions membres publiques
	//---------------------------------
	//---------------------------------
	
	protected:
	
	private:
	// Fonctions membres privées
	//---------------------------------
	/** Lis le fichier associé à la carte et charge les informations.
	 *
	 * @param chemin_fichier Le chemin du fichier à charger.
	 */
	void charger(std::string chemin_fichier);
	
	/** Libère les éléments chargés par #charger().
	 */
	void liberer();
	//---------------------------------
	
	// Attributs privés
	//---------------------------------
	//---------------------------------
	
};

#endif // CARTE_H