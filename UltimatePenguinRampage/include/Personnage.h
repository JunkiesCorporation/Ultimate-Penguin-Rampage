#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "Entite.h"

class Personnage : public Entite
{
    public:
        // Constructeurs
        Personnage(); // Initialise la postion à (0,0)
        Personnage(int x, int y);

        void subitDegats(int nbDegats); // Enlève de la vie au Personnage
        void utiliserArme(); // Enclenche l'utilisation de l'arme
    protected:
        int m_pdv;
        int m_mana;

        bool m_vivant;
    private:

};

#endif // PERSONNAGE_H
