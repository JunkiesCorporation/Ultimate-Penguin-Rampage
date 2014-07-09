#include "Carte.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Constructeur
Carte::Carte(string cheminFichier) {
    m_cheminFichier = cheminFichier;
}

void Carte::charger() {
    ifstream fichier(m_cheminFichier.c_str()); //extraction du fichier
    string ligne;

    if(fichier) {
            while(getline(fichier, ligne)) { //lit le fichier tant qu'il n'est pas finit
                cout << ligne << endl;
            }

    }
}
