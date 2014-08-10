#include "Images.h"

Texture Images::spritesJoueur[] = {*(new Texture())};
Texture Images::spritesEnnemi[] = {*(new Texture())};

void Images::chargerImages() {
    Images::spritesJoueur[DIR_BAS].charger("img/PBface.bmp");
    Images::spritesJoueur[DIR_BAS_GAUCHE].charger("img/PBbasgauche.bmp");
    Images::spritesJoueur[DIR_GAUCHE].charger("img/PBgauche.bmp");
    Images::spritesJoueur[DIR_HAUT_GAUCHE].charger("img/PBhautgauche.bmp");
    Images::spritesJoueur[DIR_HAUT].charger("img/PBdos.bmp");
    Images::spritesJoueur[DIR_HAUT_DROITE].charger("img/PBhautdroite.bmp");
    Images::spritesJoueur[DIR_DROITE].charger("img/PBdroite.bmp");
    Images::spritesJoueur[DIR_BAS_DROITE].charger("img/PBbasdroite.bmp");

    Images::spritesEnnemi[DIR_BAS].charger("img/PRface.bmp");
    Images::spritesEnnemi[DIR_BAS_GAUCHE].charger("img/PRbasgauche.bmp");
    Images::spritesEnnemi[DIR_GAUCHE].charger("img/PRgauche.bmp");
    Images::spritesEnnemi[DIR_HAUT_GAUCHE].charger("img/PRhautgauche.bmp");
    Images::spritesEnnemi[DIR_HAUT].charger("img/PRdos.bmp");
    Images::spritesEnnemi[DIR_HAUT_DROITE].charger("img/PRhautdroite.bmp");
    Images::spritesEnnemi[DIR_DROITE].charger("img/PRdroite.bmp");
    Images::spritesEnnemi[DIR_BAS_DROITE].charger("img/PRbasdroite.bmp");
}

