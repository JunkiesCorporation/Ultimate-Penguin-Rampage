#include <cmath>
#include <iostream>

#include "Joueur.h"
#include "Utils.h"
#include "Jeu.h"
#include "Constantes.h"
#include "Images.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur(Pos ptDeDepart) : Personnage(), m_reload(10), m_feu(false) {
    m_toucheDir[DIR_BAS] = false;
    m_toucheDir[DIR_BAS_GAUCHE] = false;
    m_toucheDir[DIR_GAUCHE] = false;
    m_toucheDir[DIR_HAUT_GAUCHE] = false;
    m_toucheDir[DIR_HAUT] = false;
    m_toucheDir[DIR_HAUT_DROITE] = false;
    m_toucheDir[DIR_DROITE] = false;
    m_toucheDir[DIR_BAS_DROITE] = false;

    m_sprite = &Images::spritesJoueur[DIR_BAS]; // Attribution de la premi�re texture

    // Positionnement du Joueur au centre de l'�cran
    m_pos.x = ptDeDepart.x * LARGEUR_TILE;
    m_pos.y = ptDeDepart.y * HAUTEUR_TILE;
}

void Joueur::gererEvenement(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) { // D�tecte si l'utilisateur appuie sur une touche
        switch (e.key.keysym.sym) {
        case SDLK_DOWN:
            m_toucheDir[DIR_BAS] = true;
            break;
        case SDLK_LEFT:
            m_toucheDir[DIR_GAUCHE] = true;
            break;
        case SDLK_UP:
            m_toucheDir[DIR_HAUT] = true;
            break;
        case SDLK_RIGHT:
            m_toucheDir[DIR_DROITE] = true;
            break;
        case SDLK_z:
            m_feu = true;
            break;
        case SDLK_p:
            std::cout << m_pos.x << " , " << m_pos.y << std::endl;
            break;
        }
    }

    if(e.type == SDL_KEYUP) { // D�tecte si l'utilisateur rel�che une touche
        switch (e.key.keysym.sym) {
        case SDLK_DOWN:
            m_toucheDir[DIR_BAS] = false;
            break;
        case SDLK_LEFT:
            m_toucheDir[DIR_GAUCHE] = false;
            break;
        case SDLK_UP:
            m_toucheDir[DIR_HAUT] = false;
            break;
        case SDLK_RIGHT:
            m_toucheDir[DIR_DROITE] = false;
            break;
        case SDLK_z:
            m_feu = false;
            break;
        }
    }
}

void Joueur::update(Carte const& carte) {
    deplacer(carte);

    if (m_reload > 0) { m_reload--; }

    if(m_feu && m_reload == 0){
        utiliserArme();
    }
}

void Joueur::deplacer(Carte const &carte) {
    // R�gle la direction en fonction des touches appuy�es
    if(m_toucheDir[DIR_BAS] && !(m_toucheDir[DIR_GAUCHE] || m_toucheDir[DIR_DROITE])) {
        m_direction = DIR_BAS;
    } else if(m_toucheDir[DIR_HAUT] && !(m_toucheDir[DIR_GAUCHE] || m_toucheDir[DIR_DROITE])) {
        m_direction = DIR_HAUT;
    } else if(m_toucheDir[DIR_GAUCHE] && !(m_toucheDir[DIR_HAUT] || m_toucheDir[DIR_BAS])) {
        m_direction = DIR_GAUCHE;
    } else if(m_toucheDir[DIR_DROITE] && !(m_toucheDir[DIR_HAUT] || m_toucheDir[DIR_BAS])) {
        m_direction = DIR_DROITE;
    } else if(m_toucheDir[DIR_BAS] && m_toucheDir[DIR_GAUCHE]) {
        m_direction = DIR_BAS_GAUCHE;
    } else if(m_toucheDir[DIR_HAUT] && m_toucheDir[DIR_GAUCHE]) {
        m_direction = DIR_HAUT_GAUCHE;
    } else if(m_toucheDir[DIR_HAUT] && m_toucheDir[DIR_DROITE]) {
        m_direction = DIR_HAUT_DROITE;
    } else if(m_toucheDir[DIR_BAS] && m_toucheDir[DIR_DROITE]) {
        m_direction = DIR_BAS_DROITE;
    } else {
        m_direction = DIR_IMMOBILE;
    }

    m_posPrecedente = m_pos;

    switch(m_direction) { // D�place le joueur en fonction de sa direction
        case DIR_BAS: m_pos.y += VITESSE_JOUEUR; break;
        case DIR_BAS_GAUCHE: m_pos.y += VITESSE_ANGLE; m_pos.x -= VITESSE_ANGLE; break;
        case DIR_GAUCHE: m_pos.x -= VITESSE_JOUEUR; break;
        case DIR_HAUT_GAUCHE: m_pos.y -= VITESSE_ANGLE; m_pos.x -= VITESSE_ANGLE; break;
        case DIR_HAUT: m_pos.y -= VITESSE_JOUEUR; break;
        case DIR_HAUT_DROITE: m_pos.y -= VITESSE_ANGLE; m_pos.x += VITESSE_ANGLE; break;
        case DIR_DROITE: m_pos.x += VITESSE_JOUEUR; break;
        case DIR_BAS_DROITE: m_pos.y += VITESSE_ANGLE; m_pos.x += VITESSE_ANGLE; break;
        case DIR_IMMOBILE: break;
    }

    if((m_direction != m_dirPrecedente) && (m_direction != DIR_IMMOBILE)) { // Change le sprite si n�cessaire
        m_sprite = &Images::spritesJoueur[m_direction];
    }

    if(m_direction != DIR_IMMOBILE) {
        m_dirPrecedente = m_direction;
    }

    bool coins[4]; // Vrai si le coin est en collision
    coins[0] = carte.isTileSolide(m_pos.x/LARGEUR_TILE, m_pos.y/HAUTEUR_TILE);
    coins[1] = carte.isTileSolide((m_pos.x+LARGEUR_TILE-1)/LARGEUR_TILE, m_pos.y/HAUTEUR_TILE);
    coins[2] = carte.isTileSolide((m_pos.x+LARGEUR_TILE-1)/LARGEUR_TILE, (m_pos.y+HAUTEUR_TILE-1)/HAUTEUR_TILE);
    coins[3] = carte.isTileSolide(m_pos.x/LARGEUR_TILE, (m_pos.y+HAUTEUR_TILE-1)/HAUTEUR_TILE);
    if(coins[0] && coins[1]) {
        m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
    }
    if(coins[1] && coins[2]) {
        m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
    }
    if(coins[2] && coins[3]) {
        m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
    }
    if(coins[3] && coins[0]) {
        m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
    }
    if (coins[0] && !(coins[1] || coins[2] || coins[3])) {
        switch(m_direction) {
        case DIR_GAUCHE: m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
            break;
        case DIR_HAUT: m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
            break;
        case DIR_HAUT_DROITE: m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
            break;
        case DIR_BAS_GAUCHE: m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
            break;
        case DIR_HAUT_GAUCHE:
            if (m_posPrecedente.x - (m_pos.x / LARGEUR_TILE + 1)*LARGEUR_TILE > m_posPrecedente.y - (m_pos.y / HAUTEUR_TILE + 1)*HAUTEUR_TILE) {
                m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
            } else {
                m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
            }
            break;
        default:
            break;
        }
    }
    if (coins[1] && !(coins[0] || coins[2] || coins[3])) {
        switch(m_direction) {
        case DIR_DROITE: m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
            break;
        case DIR_HAUT: m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
            break;
        case DIR_HAUT_GAUCHE: m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
            break;
        case DIR_BAS_DROITE: m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
            break;
        case DIR_HAUT_DROITE:
            if((m_pos.x/LARGEUR_TILE)*LARGEUR_TILE - m_posPrecedente.x > m_posPrecedente.y - (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE) {
                m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
            } else {
                m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
            }
            break;
        default:
            break;
        }
    }
    if (coins[2] && !(coins[0] || coins[1] || coins[3])) {
        switch(m_direction) {
        case DIR_DROITE: m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
            break;
        case DIR_BAS: m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
            break;
        case DIR_BAS_GAUCHE: m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
            break;
        case DIR_HAUT_DROITE: m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
            break;
        case DIR_BAS_DROITE:
            if((m_pos.x/LARGEUR_TILE)*LARGEUR_TILE - m_posPrecedente.x > (m_pos.y/HAUTEUR_TILE)*HAUTEUR_TILE - m_posPrecedente.y) {
                m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
            } else {
                m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
            }
            break;
        default:
            break;
        }
    }
    if (coins[3] && !(coins[0] || coins[1] || coins[2])) {
        switch(m_direction) {
        case DIR_GAUCHE: m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
            break;
        case DIR_BAS: m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
            break;
        case DIR_BAS_DROITE: m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
            break;
        case DIR_HAUT_GAUCHE: m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
            break;
        case DIR_BAS_GAUCHE:
            if(m_posPrecedente.x - (m_pos.x/LARGEUR_TILE + 1)*LARGEUR_TILE > (m_pos.y/HAUTEUR_TILE)*HAUTEUR_TILE - m_posPrecedente.y) {
                m_pos.x = (m_pos.x/LARGEUR_TILE + 1) * LARGEUR_TILE;
            } else {
                m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
            }
            break;
        default:
            break;
        }
    }


}

void Joueur::utiliserArme() {
    if(m_reload == 0) {
        m_reload = 10;
        Jeu::projectiles.push_back(new Projectile(m_pos.x, m_pos.y, m_dirPrecedente, 7));
    }
}
