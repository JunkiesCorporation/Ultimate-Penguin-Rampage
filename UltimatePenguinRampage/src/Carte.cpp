#include "Carte.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Carte::Carte() {

}

void Carte::extraire(string m_nomFichier) {
    ifstream fichier("map/1.txt"); //extraction du fichier
    string ligne;

    if(fichier) {
            while(getline(fichier, ligne)) { //lit le fichier tant qu'il n'est pas finit
                cout << ligne << endl;
            }

    }
}
