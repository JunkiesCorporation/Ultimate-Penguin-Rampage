#ifndef CARTE_H
#define CARTE_H
#include <string>


class Carte
{
    public:
        Carte();
        void extraire(std::string m_nomFichier);
    protected:
    private:
        int m_tableau[100];
        std::string m_nomFichier;
};

#endif // CARTE_H
