#ifndef UPR_H
#define UPR_H

#include <SDL.h>

#include "Jeu.h"
#include "Profil.h"

/** La classe principale du programme.
 *
 * Contient la fenêtre du programme ainsi que son renderer.
 * Contient également les diverses dimensions constantes utilisées dans le programme.
 *
 * Permet le lancement du programme via la fonction #lancer().
 *
 * \todo Changer les variables contenant la position des images du menu principal.
 */
class UPR
{
	public:
		// Constructeurs
		//-----------------------------
		/** Constructeur par défaut.
		 *
		 * Seul et unique constructeur d'UPR, initialise les attributs du programme.
		 */
		UPR();
		//-----------------------------
		
		// Destructeur
		//-----------------------------
		/** Destructeur par défaut.
		 */
		~UPR();
		//-----------------------------
		
		// Fonctions membres publiques
		//-----------------------------
		/** Fonction responsable du programme.
		 *
		 * 1. Appelle #menuPrincipal() pour gérer l'affichage du menu principal et récupérer le choix de l'utilisateur.
		 * 2. Agit en conséquence des choix de l'utilisateur de deux manières distinctes :
		 *   - Démarre #instance_jeu avec #profil_joueur si l'utilisateur choisi de jouer.
		 *   - Quitte le programme si l'utilisateur à choisi de quitter.
		 */
		void lancer();
		//-----------------------------
		
		// Attributs publics statiques
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
		/** Gère le chargement d'un ancien profil.
		 *
		 * Propose de sélectionner parmi les différents emplacements de sauvegarde puis configure #profil_joueur selon la sauvegarde choisie.
		 *
		 * \todo Code et description pour le chargement d'un nouveau profil.
		 *
		 * @return Si le chargement du profil a réussi.
		 */
		bool chargerProfil();
		
		/** Affiche et gère le menu principal.
		 *
		 * 1. Permet à l'utilisateur de sélectionner l'un des choix du menu principal à l'aide des flèches haut et bas et de la touche "retour". Les 4 options sont :
		 *   1. Nouveau profil.
		 *   2. Charger profil.
		 *   3. Options.
		 *   4. Quitter.
		 *
		 * 2. Agit selon le choix de l'utilisateur :
		 *   1. Nouveau profil : appelle #nouveauProfil() et se termine si la création du profil est réussie.
		 *   2. Charger profil : appelle #chargerProfil() et se termine si le chargement du profil est réussi.
		 *   3. Options : _cf. à faire_.
		 *   4. Quitter : quitte le menu principal sans confirmation.
		 *
		 * 3. Au moment de quitter, renvoie le choix final de l'utilisateur.
		 *
		 * @return Le numéro de l'option choisie.
		 */
		int menuPrincipal();
		
		/** Gère la création d'un nouveau profil.
		 *
		 * Guide l'utilisateur pendant la création d'un nouveau profil et modifie #profil_joueur en conséquence.
		 *
		 * \todo Code et description pour la création d'un nouveau profil.
		 *
		 * @return Si la création du profil a réussi.
		 */
		bool nouveauProfil();
		//-----------------------------
		
		// Attributs privés
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