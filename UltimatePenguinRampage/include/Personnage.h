#ifndef PERSONNAGE_H
#define PERSONNAGE_H


class Personnage
{
    public:
        Personnage();
        void recevoirDegats(int nbDegats);
        void utiliseArme();

    protected:
    private:
        int m_pdv; // les points de vie
        int m_mana; // les points de mana
        bool m_vivant; // true=vivant false=mort
        int m_posX; // position du personnage sur l'axe des x.
        int m_posY; // position du personnage sur l'axe des y.
        int m_type; // (1)=Joueur (2)=IA

};

#endif // PERSONNAGE_H
