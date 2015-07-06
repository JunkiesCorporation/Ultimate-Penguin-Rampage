#ifndef ARENE_H
#define ARENE_H

#include "Carte.h"

/** Objet permettant le contrôle d'un niveau jouable.
 */ 
class Arene
{
	public:
	// Constructeurs
	//---------------------------------
	/** Constructeur par défaut.
	 * 
	 * Initialise les attributs à des valeurs par défaut.
	 */
	Arene();
	//---------------------------------
	
	// Destructeur
	//---------------------------------
	/** Destructeur par défaut.
	 */
	~Arene();
	//---------------------------------
	
	// Fonctions membres publiques
	//---------------------------------
	/** Charge les éléments requis pour le fonctionnement de cette instance d'Arene.
	 */
	void charger();
	
	/** Lance l'arène si elle a été précédemment correctement préparée à l'aide de #charger().
	 */
	void lancer();
	
	/** Réinitialise une arène lancée et terminée.
	 *
	 * Permet de réutiliser la même instance d'Arene afin de ne pas encombrer la mémoire en chargeant toutes les arènes du jeu d'un coup.
	 */
	void reinitialiser();
	//---------------------------------
	
	protected:
	
	private:
	// Attributs privés
	//---------------------------------
	/** La carte de l'arène.
	 */
	Carte m_carte
	
	/** Si cette instance d'Arene est prête à être lancée.
	 */
	bool m_est_prete;
	//---------------------------------
	
};

#endif // ARENE_H