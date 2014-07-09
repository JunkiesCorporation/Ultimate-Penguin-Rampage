#ifndef CARTE_H
#define CARTE_H
#include <string>


class Carte
{
    public:
        Carte(std::string); // Constructeur

    protected:
    private:
        void charger(); // Lis le fichier associ� � la carte

        int m_tableau[100]; // Contient les donn�es de la carte
        std::string m_cheminFichier; // Chemin du fichier � charger
};

#endif // CARTE_H
