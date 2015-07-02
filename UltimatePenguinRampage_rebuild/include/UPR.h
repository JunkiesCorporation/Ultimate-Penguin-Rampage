#ifndef UPR_H
#define UPR_H

#include <SDL.h>

#include "Jeu.h"
#include "Profil.h"

/** La classe principale du programme.
 * Contient la fenêtre ainsi que sa surface et son renderer.
 * Contient également les diverses dimensions constantes utilisées dans le programme.
 *
 * \todo Changer les variables contenant la position des images du menu principal.
 */
class UPR
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 * Seul et unique constructeur d'UPR, initialise les attributs du programme.
		 */
		UPR();
		//-----------------------------
		
		// Destructeurs
		//-----------------------------
		/** Destructeur par défaut.
		 */
		~UPR();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Fonction responsable du programme.
		 * Commence par afficher le menu principal puis fait tourner l'ensemble du jeu.
		 */
		void lancer();
		//-----------------------------
		
		// Attributs membres publiques et static
		//-----------------------------
		/** Largeur de l'écran (= 25 tiles).
		 */
		static const int LARGEUR_ECRAN = 800;
		
		/** Hauteur de l'écran (= 20 tiles).
		 */
		static const int HAUTEUR_ECRAN = 640;
		
		/** FPS maximum du jeu.
		 */
		static const int FPS_ECRAN = 60;
		
		/** Ticks écran par image.
		 */
		static const int TICKS_ECRAN_PAR_IMAGE = 1000 / FPS_ECRAN;
		
		/** La fenêtre du programme.
		 * 
		 * Créée dans Utils::initialisationSDL().
		 *
		 * Détruite dans Utils::quitter().
		 */
		static SDL_Window* fenetre_SDL; 
		
		/** Le renderer de UPR::fenetre_SDL.
		 * 
		 * Créé dans Utils::initialisationSDL().
		 * 
		 * Détruit dans Utils::quitter();
		 */
		static SDL_Renderer* renderer_SDL;
		//-----------------------------
	
	protected:
	
	private:
		// Fonctions membres privées
		//-----------------------------
		/** Gère l'affichage et le contrôle du menu principal.
		 * @return Le numéro de l'option choisie.
		 */
		int menuPrincipal();
		
		/** Gère la création d'un nouveau profil.
		 * Affiche la suite d'écrans nécessaires à la création d'un nouveau profil et modifie #profil_joueur en conséquence.
		 *
		 * \todo le code pour la création d'un nouveau profil.
		 *
		 * @return Si la création du profil a réussi.
		 */
		bool nouveauProfil();
		
		/** Gère le chargement d'un ancien profil.
		 * Propose de charger les différents emplacements de sauvegarde puis configure #profil_joueur selon la sauvegarde.
		 *
		 * \todo le code pour le chargement d'un nouveau profil.
		 *
		 * @return Si le chargement du profil a réussi.
		 */
		bool chargerProfil();
		//-----------------------------
		
		// Attributs membres privés
		//-----------------------------
		/** L'instance du Jeu
		 */
		Jeu instance_jeu;
		
		/** Le profil utilisé par le joueur.
		 */
		Profil profil_joueur;
		//-----------------------------
};
#endif // UPR_H