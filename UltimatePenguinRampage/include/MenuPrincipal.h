#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "Texture.h"

class MenuPrincipal
{
    public:
		int static menuPrincipal();
		
    protected:
    private:
		void static chargerTextures();
		void static supprimerTextures();
		
		static SDL_Surface* m_menu_principal;
};

#endif // MENUPRINCIPAL_H
