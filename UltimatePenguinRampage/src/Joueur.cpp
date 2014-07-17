#include <cmath>
#include <iostream>

#include "Joueur.h"
#include "Utils.h"
#include "Jeu.h"
#include "Constantes.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur() : Personnage(), m_reload(10), m_feu(false)
{
    m_toucheDir[DIR_BAS] = false;
    m_toucheDir[DIR_BAS_GAUCHE] = false;
    m_toucheDir[DIR_GAUCHE] = false;
    m_toucheDir[DIR_HAUT_GAUCHE] = false;
    m_toucheDir[DIR_HAUT] = false;
    m_toucheDir[DIR_HAUT_DROITE] = false;
    m_toucheDir[DIR_DROITE] = false;
    m_toucheDir[DIR_BAS_DROITE] = false;

    // Chargement des 8 textures du Joueur
    m_sprites[DIR_BAS].charger("img/PBface.bmp");
    m_sprites[DIR_BAS_GAUCHE].charger("img/PBbasgauche.bmp");
    m_sprites[DIR_GAUCHE].charger("img/PBgauche.bmp");
    m_sprites[DIR_HAUT_GAUCHE].charger("img/PBhautgauche.bmp");
    m_sprites[DIR_HAUT].charger("img/PBdos.bmp");
    m_sprites[DIR_HAUT_DROITE].charger("img/PBhautdroite.bmp");
    m_sprites[DIR_DROITE].charger("img/PBdroite.bmp");
    m_sprites[DIR_BAS_DROITE].charger("img/PBbasdroite.bmp");

    m_sprite = &m_sprites[DIR_BAS]; // Attribution de la première texture

    // Positionnement du Joueur au centre de l'écran
    m_pos.x = (LARGEUR_ECRAN - m_sprite->getLargeur()) / 2;
    m_pos.y = (HAUTEUR_ECRAN - m_sprite->getHauteur()) / 2;
}

void Joueur::gererEvenement(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) { // Détecte si l'utilisateur appuie sur une touche
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
        }
    }

    if(e.type == SDL_KEYUP) { // Détecte si l'utilisateur relâche une touche
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
    // Règle la direction en fonction des touches appuyées
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

    switch(m_direction) { // Déplace le joueur en fonction de sa direction
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

    if((m_direction != m_dirPrecedente) && (m_direction != DIR_IMMOBILE)) { // Change le sprite si nécessaire
        m_sprite = &m_sprites[m_direction];
    }

    if(m_direction != DIR_IMMOBILE) {
        m_dirPrecedente = m_direction;
    }

    // Faudrait quand même pas qu'il sorte de l'écran ce pingouin
    if(m_pos.x < 0) { m_pos.x = 0; }
    if(m_pos.x + m_sprite->getLargeur() > LARGEUR_ECRAN) { m_pos.x = LARGEUR_ECRAN - m_sprite->getLargeur(); }
    if(m_pos.y < 0) { m_pos.y = 0; }
    if(m_pos.y + m_sprite->getHauteur() > HAUTEUR_ECRAN) { m_pos.y = HAUTEUR_ECRAN - m_sprite->getHauteur(); }

    // TODO Putain de collision de merde
    bool coins[4]; // Vrai si le coin est en collision
    coins[0] = carte.isTileSolide(m_pos.x/LARGEUR_TILE, m_pos.y/HAUTEUR_TILE);
    coins[1] = carte.isTileSolide(m_pos.x/LARGEUR_TILE + 1, m_pos.y/HAUTEUR_TILE);
    coins[2] = carte.isTileSolide(m_pos.x/LARGEUR_TILE + 1, m_pos.y/HAUTEUR_TILE + 1);
    coins[3] = carte.isTileSolide(m_pos.x/LARGEUR_TILE, m_pos.y/HAUTEUR_TILE + 1);
    if(coins[0] && coins[1]) {
        m_pos.y = (m_pos.y/HAUTEUR_TILE + 1) * HAUTEUR_TILE;
    } if(coins[1] && coins[2]) {
        m_pos.x = (m_pos.x/LARGEUR_TILE) * LARGEUR_TILE;
    } if(coins[2] && coins[3]) {
        m_pos.y = (m_pos.y/HAUTEUR_TILE) * HAUTEUR_TILE;
    } if(coins[3] && coins[0]) {
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

}

void Joueur::utiliserArme() {
    if(m_reload == 0) {
        m_reload = 10;
        Jeu::projectiles.push_back(new Projectile(m_pos.x, m_pos.y, m_dirPrecedente, 7));
    }
}
