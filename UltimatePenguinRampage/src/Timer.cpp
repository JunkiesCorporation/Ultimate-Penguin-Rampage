#include <SDL.h>

#include "Timer.h"

// Constructeur
//-------------------------------------
/* Constructeur par défaut.*/
Timer::Timer()
{
	// Initialisation du nombre de ticks au départ à 0.
	m_ticks_depart = 0;
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Démarre le Timer.*/
void Timer::start()
{
	// Récupération du temps système actuel.
	m_ticks_depart = SDL_GetTicks();
}

/* Retourne le nombre de ticks écoulé depuis le démarrage du Timer.*/
Uint32 Timer::getTicks()
{
	// Retour de la différence entre le temps système actuel et le temps de départ.
	return SDL_GetTicks() - m_ticks_depart;
}
//-------------------------------------