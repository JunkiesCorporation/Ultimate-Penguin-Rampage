#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Carte.h"
#include "Constantes.h"

// Constructeur
Carte::Carte(std::string cheminFichier) : m_largeur(0), m_hauteur(0), m_data(NULL),
        m_cheminFichier(cheminFichier)
{
    m_ptDeDepart.x = 0;
    m_ptDeDepart.y = 0;
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
        // Lecture du [header]
        fichier >> ligne;
        if(ligne != "[header]") {
            std::cout << "Erreur : [header] manquant dans : " << m_cheminFichier << std::endl;
        }

        fichier >> ligne; fichier >> ligne; // Lecture de la largeur
        m_largeur = atoi(ligne.c_str());
        fichier >> ligne; fichier >> ligne; // Lecture de la hauteur
        m_hauteur = atoi(ligne.c_str());

        // Creation de la grille de données
        m_data = new int*[m_largeur];
        for(int i(0); i < m_largeur; i++) {
            m_data[i] = new int[m_hauteur];
        }

        // Lecture des [infos_joueur]
        fichier >> ligne;
        if(ligne != "[infos_joueur]") {
            std::cout << "Erreur : [infos_joueur] manquant dans : " << m_cheminFichier << std::endl;
        }

        fichier >> ligne; fichier >> ligne; // Lecture des coordonnées de départ du joueur
        m_ptDeDepart.x = atoi(ligne.c_str());
        fichier >> ligne;
        m_ptDeDepart.y = atoi(ligne.c_str());

        // Lecture du [tileset]
        fichier >> ligne;
        if(ligne != "[tilesets]") {
            std::cout << "Erreur : [tileset] manquant dans : " << m_cheminFichier << std::endl;
        }

        fichier >> ligne; fichier >> ligne; // Lecture du chemin du Tileset
        std::string cheminTileset(ligne);


        // Réinitialisation du Tileset avec le nouveau Fichier
        (&m_tileset)->~Tileset();
        new (&m_tileset) Tileset(cheminTileset);

        fichier >> ligne;
        if(ligne != "[data]") {
            std::cout << "Erreur : [data] manquant dans : " << m_cheminFichier << std::endl;
        }

        // Lecture des données de la Carte
        for(int y(0); y < m_hauteur; y++) {
            for(int x(0); x < m_largeur; x++) {
                fichier >> ligne;
                m_data[x][y] = atoi(ligne.c_str());
            }
        }

        fichier.close(); // Fermeture du fichier
    } else {
        std::cout << "Erreur : Echec du chargement de " << m_cheminFichier << std::endl;
    }
}

void Carte::render(SDL_Rect camera) const {
    int h = m_tileset.getHauteurTiles();
    int l = m_tileset.getLargeurTiles();

    bool coins[4];

    for(int y(0); y < m_hauteur; y++) {
        for(int x(0); x < m_largeur; x++) {
            coins[0] = x*l > camera.x && x*l < camera.x + LARGEUR_ECRAN && y*h > camera.y && y*h < camera.y + HAUTEUR_ECRAN;
            coins[1] = x*l + l > camera.x && x*l + l < camera.x + LARGEUR_ECRAN && y*h > camera.y && y*h < camera.y + HAUTEUR_ECRAN;
            coins[2] = x*l + l > camera.x && x*l + l < camera.x + LARGEUR_ECRAN && y*h + h > camera.y && y*h + h < camera.y + HAUTEUR_ECRAN;
            coins[3] = x*l > camera.x && x*l < camera.x + LARGEUR_ECRAN && y*h + h > camera.y && y*h + h < camera.y + HAUTEUR_ECRAN;
            if(coins[0]||coins[1]||coins[2]||coins[3]) {
                m_tileset.render(m_data[x][y], x*l - camera.x, y*h - camera.y);
            }
        }
    }
}

bool Carte::isTileSolide(int x, int y) const {
    return m_tileset.isTileSolide(m_data[x][y]);
}

int Carte::getHauteur() const {
    return m_hauteur;
}
int Carte::getLargeur() const {
    return m_largeur;
}
Pos Carte::getPtDeDepart() const {
    return m_ptDeDepart;
}
