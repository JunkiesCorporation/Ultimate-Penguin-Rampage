#include <SDL.h>

#include "Timer.h"

// Constructeur
//-------------------------------------
/* Constructeur par défaut.*/
Timer::Timer() : m_ticks_depart(0)
{
	
}
//-------------------------------------

// Fonctions membres publiques
//-------------------------------------
/* Démarre le Timer.*/
void Timer::start()
{
	// On récupère le temps système actuel.
	m_ticks_depart = SDL_GetTicks();
}

/* Retourne le nombre de ticks écoulé depuis le démarrage du Timer.*/
Uint32 Timer::getTicks()
{
	return SDL_GetTicks() - m_ticks_depart;
}
//-------------------------------------