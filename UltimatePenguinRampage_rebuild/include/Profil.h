#ifndef PROFIL_H
#define PROFIL_H

#include <string>

/** Classe du profil du joueur.
 *
 * *En construction au fur et à mesure de l'avancée de la première version jouable d'Ultimate Penguin Rampage.*
 *
 * Contient toutes les informations concernant le profil du joueur avec lequel une instance de Jeu peut se #Jeu::lancer(). Actuellement ces informations sont :
 * - L'emplacement de sauvegarde que le profil doit utiliser.
 * - Le nom du profil.
 * - S'il s'agit d'un profil nouvellement créé (sera peut-être remplacé par un marqueur d'avancée dans l'histoire).
 *
 * Plus tard, on peut imaginer que les informations suivantes seront également contenues ici.
 * - Avancée du joueur dans l'histoire.
 * - Avancée du joueur dans les arènes.
 * - Développement de la base secrète du joueur.
 * - Caractéristiques du héros du joueur. (Statistiques, avancement des compétences, inventaire, armes, etc.)
 * - etc.
 */
class Profil
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Initialise les attributs membres de Profil à des valeurs par défaut.
		 */
		Profil();
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 */
		~Profil();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Retourne le nom du Profil.
		 *
		 * @return m_nom_du_profil Le nom du Profil.
		 */
		std::string getNomProfil() const;
		
		/** Change l'emplacement de sauvegarde du profil.
		 *
		 * @param p_emplacement_sauvegarde Le nouvel emplacement du sauvegarde.
		 */
		void setEmplacementSauvegarde(int p_emplacement_sauvegarde);
		
		/** Change le nom du profil.
		 *
		 * @param p_nom_du_profil Le nouveau nom du profil.
		 */
		void setNomProfil(std::string p_nom_du_profil);
		
		/** Change s'il s'agit d'un nouveau profil ou non.
		 *
		 * @param p_nouveau Si c'est un nouveau profil.
		 */
		void setSiNouveau(bool p_nouveau);
		//-----------------------------
	
	protected:
	
	private:
		// Attributs membres privés.
		//-----------------------------
		/** Numéro de l'emplacement de sauvegarde de ce profil.
		 */
		int m_emplacement_sauvegarde;
		
		/** Le nom du profil.
		 */
		std::string m_nom_du_profil;
		
		/** S'il s'agit d'un nouveau profil ou non.
		 */
		bool m_nouveau;
		//-----------------------------
};

#endif // PROFIL_H