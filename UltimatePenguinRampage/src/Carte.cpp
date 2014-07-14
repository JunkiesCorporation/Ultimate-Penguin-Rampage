#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Carte.h"

// Constructeur
Carte::Carte(std::string cheminFichier) : m_largeur(0), m_hauteur(0), m_data(NULL),
        m_cheminFichier(cheminFichier)
{
    charger();
}

Carte::~Carte() {
    std::cout << "Carte detruite" << std::endl;
    if(m_data != NULL) {
        for(int i(0); i < m_largeur; i++) {
            delete [] m_data[i];
        }
        delete [] m_data;
    }
}

void Carte::charger() {
    std::ifstream fichier(m_cheminFichier.c_str()); //extraction du fichier
    std::string ligne;

    if(fichier) {
        fichier >> ligne;
        if(ligne != "[header]") {
            std::cout << "Erreur : [header] manquant dans : " << m_cheminFichier << std::endl;
        }
        fichier >> ligne; fichier >> ligne;
        m_largeur = atoi(ligne.c_str());
        fichier >> ligne; fichier >> ligne;
        m_hauteur = atoi(ligne.c_str());

        m_data = new int*[m_largeur];
        for(int i(0); i < m_largeur; i++) {
            m_data[i] = new int[m_hauteur];
        }

        fichier >> ligne;
        if(ligne != "[tileset]") {
            std::cout << "Erreur : [tileset] manquant dans : " << m_cheminFichier << std::endl;
        }
        fichier >> ligne; fichier >> ligne;
        std::string cheminTileset(ligne);
        fichier >> ligne;
        int largeurTiles(atoi(ligne.c_str()));
        fichier >> ligne;
        int hauteurTiles(atoi(ligne.c_str()));
        fichier >> ligne;
        int largeurTileset(atoi(ligne.c_str()));
        fichier >> ligne;
        int hauteurTileset(atoi(ligne.c_str()));

        (&m_tileset)->~Tileset();
        new (&m_tileset) Tileset(largeurTileset, hauteurTileset, largeurTiles, hauteurTiles, cheminTileset);

        fichier >> ligne;
        if(ligne != "[data]") {
            std::cout << "Erreur : [data] manquant dans : " << m_cheminFichier << std::endl;
        }

        for(int y(0); y < m_hauteur; y++) {
            for(int x(0); x < m_largeur; x++) {
                fichier >> ligne;
                m_data[x][y] = atoi(ligne.c_str());
            }
        }

        fichier.close();
    } else {
        std::cout << "Erreur : Echec du chargement de " << m_cheminFichier << std::endl;
    }
}

void Carte::render() {
    for(int y(0); y < m_hauteur; y++) {
        for(int x(0); x < m_largeur; x++) {
            m_tileset.render(m_data[x][y], x, y);
        }
    }
}
