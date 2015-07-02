#ifndef JEU_H
#define JEU_H

#include "Profil.h"
#include "Texture.h"

/** La classe qui contient le déroulement du jeu une fois lancé à partir du menu principal.
 * \todo Documentation de Jeu.
 * \todo Choisir le constructeur pour initialiser le Jeu.
 */
class Jeu
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 * Appelé lors de la création d'une instance de Jeu.
		 * 
		 * Initialise les attributs du Jeu avec des valeurs par défaut.
		 */
		Jeu();
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 */
		~Jeu();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Lance le jeu avec les données du Profil donné.
		 *
		 * @param profil_joueur Le profil utilisé par le joueur.
		 */
		void lancer(Profil* profil_joueur);
		//-----------------------------
	
	protected:
	
	private:
		// Fonctions membres privées
		//-----------------------------
		void chargerTexturesEcran();
		
		void libererTexturesEcran();
		//-----------------------------
		
		// Attributs membres privés
		//-----------------------------
		Texture* m_texture_cadre_selection;
		
		Texture* m_texture_fond_jeu;
		
		Texture* m_texture_mode_arene;
		
		Texture* m_texture_mode_histoire;
		//-----------------------------
	
};

#endif // JEU_H