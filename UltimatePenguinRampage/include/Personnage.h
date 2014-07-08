#ifndef PERSONNAGE_H
#define PERSONNAGE_H


class Personnage
{
    public:
        Personnage();
        void subitDegats(int nbDegats);
        void utiliserArme();
    protected:
    private:
        int m_pdv;
        int m_mana;
        int m_posX;
        int m_posY;
        bool m_vivant;
};

#endif // PERSONNAGE_H
