#include <cmath>
#include <iostream>

#include "Joueur.h"
#include "Utils.h"
#include "Jeu.h"

const int VITESSE_JOUEUR = 3;
const int VITESSE_ANGLE = VITESSE_JOUEUR * cos(M_PI_4);

Joueur::Joueur() : Personnage(), reload(10), vitX(0), vitY(0), feu(false)
{
    toucheDir[DIR_BAS] = false;
    toucheDir[DIR_BAS_GAUCHE] = false;
    toucheDir[DIR_GAUCHE] = false;
    toucheDir[DIR_HAUT_GAUCHE] = false;
    toucheDir[DIR_HAUT] = false;
    toucheDir[DIR_HAUT_DROITE] = false;
    toucheDir[DIR_DROITE] = false;
    toucheDir[DIR_BAS_DROITE] = false;

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
    m_posX = (Utils::SCREEN_WIDTH - m_sprite->getLargeur()) / 2;
    m_posY = (Utils::SCREEN_HEIGHT - m_sprite->getHauteur()) / 2;
}

void Joueur::gererEvenement(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) { // Détecte si l'utilisateur appuie sur une touche
        switch (e.key.keysym.sym) {
        case SDLK_DOWN:
            toucheDir[DIR_BAS] = true;
            break;
        case SDLK_LEFT:
            toucheDir[DIR_GAUCHE] = true;
            break;
        case SDLK_UP:
            toucheDir[DIR_HAUT] = true;
            break;
        case SDLK_RIGHT:
            toucheDir[DIR_DROITE] = true;
            break;
        case SDLK_z:
            feu = true;
            break;
        }
    }

    if(e.type == SDL_KEYUP) { // Détecte si l'utilisateur relâche une touche
        switch (e.key.keysym.sym) {
        case SDLK_DOWN:
            toucheDir[DIR_BAS] = false;
            break;
        case SDLK_LEFT:
            toucheDir[DIR_GAUCHE] = false;
            break;
        case SDLK_UP:
            toucheDir[DIR_HAUT] = false;
            break;
        case SDLK_RIGHT:
            toucheDir[DIR_DROITE] = false;
            break;
        case SDLK_z:
            feu = false;
            break;
        }
    }
}

void Joueur::update(std::vector<Projectile*> &projectiles) {
    deplacer();

    if (reload > 0) { reload--; }

    if(feu && reload == 0){
        tirer(projectiles);
    }
}

void Joueur::deplacer() {
    // Règle la direction en fonction des touches appuyées
    if(toucheDir[DIR_BAS] && !(toucheDir[DIR_GAUCHE] || toucheDir[DIR_DROITE])) {
        m_direction = DIR_BAS;
    } else if(toucheDir[DIR_HAUT] && !(toucheDir[DIR_GAUCHE] || toucheDir[DIR_DROITE])) {
        m_direction = DIR_HAUT;
    } else if(toucheDir[DIR_GAUCHE] && !(toucheDir[DIR_HAUT] || toucheDir[DIR_BAS])) {
        m_direction = DIR_GAUCHE;
    } else if(toucheDir[DIR_DROITE] && !(toucheDir[DIR_HAUT] || toucheDir[DIR_BAS])) {
        m_direction = DIR_DROITE;
    } else if(toucheDir[DIR_BAS] && toucheDir[DIR_GAUCHE]) {
        m_direction = DIR_BAS_GAUCHE;
    } else if(toucheDir[DIR_HAUT] && toucheDir[DIR_GAUCHE]) {
        m_direction = DIR_HAUT_GAUCHE;
    } else if(toucheDir[DIR_HAUT] && toucheDir[DIR_DROITE]) {
        m_direction = DIR_HAUT_DROITE;
    } else if(toucheDir[DIR_BAS] && toucheDir[DIR_DROITE]) {
        m_direction = DIR_BAS_DROITE;
    } else {
        m_direction = DIR_IMMOBILE;
    }

    switch(m_direction) { // Déplace le joueur en fonction de sa direction
        case DIR_BAS: m_posY += VITESSE_JOUEUR; break;
        case DIR_BAS_GAUCHE: m_posY += VITESSE_ANGLE; m_posX -= VITESSE_ANGLE; break;
        case DIR_GAUCHE: m_posX -= VITESSE_JOUEUR; break;
        case DIR_HAUT_GAUCHE: m_posY -= VITESSE_ANGLE; m_posX -= VITESSE_ANGLE; break;
        case DIR_HAUT: m_posY -= VITESSE_JOUEUR; break;
        case DIR_HAUT_DROITE: m_posY -= VITESSE_ANGLE; m_posX += VITESSE_ANGLE; break;
        case DIR_DROITE: m_posX += VITESSE_JOUEUR; break;
        case DIR_BAS_DROITE: m_posY += VITESSE_ANGLE; m_posX += VITESSE_ANGLE; break;
        case DIR_IMMOBILE: break;
    }

    if((m_direction != m_dirPrecedente) && (m_direction != DIR_IMMOBILE)) { // Change le sprite si nécessaire
        m_sprite = &m_sprites[m_direction];
    }

    if(m_direction != DIR_IMMOBILE) {
        m_dirPrecedente = m_direction;
    }

    // Faudrait quand même pas qu'il sorte de l'écran ce pingouin
    if(m_posX < 0) { m_posX = 0; }
    if(m_posX + m_sprite->getLargeur() > Utils::SCREEN_WIDTH) { m_posX = Utils::SCREEN_WIDTH - m_sprite->getLargeur(); }
    if(m_posY < 0) { m_posY = 0; }
    if(m_posY + m_sprite->getHauteur() > Utils::SCREEN_HEIGHT) { m_posY = Utils::SCREEN_HEIGHT - m_sprite->getHauteur(); }

}

void Joueur::tirer(std::vector<Projectile*> &projectiles) {
    if(reload == 0) {
        reload = 10;
        projectiles.push_back(new Projectile(m_posX, m_posY, m_dirPrecedente, 7));
    }
}
