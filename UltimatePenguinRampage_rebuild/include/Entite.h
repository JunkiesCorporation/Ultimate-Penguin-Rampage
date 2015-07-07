#ifndef ENTITE_H
#define ENTITE_H

/** Classe abstraite qui regroupe toutes les fonctionnalités communes aux entités qui apparaissent dans une arène.
 */
class Entite
{
	public:
		// Constructeurs
		//---------------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs à des valeurs par défaut.
		 */
		Entite();
		//---------------------------------
		
		// Destructeur
		//---------------------------------
		/** Destructeur par défaut.
		 *
		 * Il est virtuel car une classe abstraite ne peut avoir de destructeur.
		 */
		virtual ~Entite();
		//---------------------------------
		
		// Fonctions membres publiques
		//---------------------------------
		/** Met à jour l'entité.
		 *
		 * Toutes les actions que l'entité effectue au cours du niveau partent de cette fonction.
		 */
		virtual void update() = 0;
		//---------------------------------
	
	protected:
		// Attributs protégés
		//---------------------------------
		//---------------------------------
	
	private:
	
};

#endif // ENTITE_H