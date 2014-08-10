#include <iostream>

#include "Texture.h"
#include "Utils.h"

static int nombre(0);

Texture::Texture() : m_image(NULL), m_largeur(0), m_hauteur(0)
{
}

Texture::Texture(std::string cheminImage) : m_image(NULL), m_largeur(0), m_hauteur(0)
{
    charger(cheminImage);
}

Texture::~Texture()
{
    liberer();
}

void Texture::charger(std::string cheminImage) {
    nombre++;
    liberer(); // Liberation de la texture précédente

    SDL_Texture* nouvelleTexture = NULL;
    SDL_Surface* imageChargee = SDL_LoadBMP(cheminImage.c_str()); // Chargement de l'image Bitmap
    if(imageChargee == NULL) { // Gestion de l'échec du chargement de l'image
        std::cout << "Erreur : L'image " << cheminImage << " n'a pas pu etre chargee." << std::endl;
    } else {
        SDL_SetColorKey(imageChargee, SDL_TRUE, SDL_MapRGB(imageChargee->format, 255, 0, 255)); // Activation de la transparence

        nouvelleTexture = SDL_CreateTextureFromSurface(Utils::renderer, imageChargee); // Création de la texture
        if(nouvelleTexture == NULL) { // Gestion de l'échec de la création de la texture
            std::cout << "Erreur : La texture n'a pas pu etre creee." << std::endl;
        } else {
            m_largeur = imageChargee->w; // Récupération des données de l'image chargée
            m_hauteur = imageChargee->h;
        }

        SDL_FreeSurface(imageChargee);
    }

    m_image = nouvelleTexture;
}

void Texture::liberer() {
    if(m_image != NULL) {
        nombre--;
        std::cout << "Textures restantes: " << nombre << std::endl;
        SDL_DestroyTexture(m_image);
        m_image = NULL;
        m_largeur = 0;
        m_hauteur = 0;
    }
}

void Texture::render(int x, int y) const {
    SDL_Rect renderQuad = {x, y, m_largeur, m_hauteur}; // Le rectangle sur lequel la texture est projetée
    SDL_RenderCopy(Utils::renderer, m_image, NULL, &renderQuad);
}

SDL_Texture* Texture::getImage() const {
    return m_image;
}
int Texture::getLargeur() const {
    return m_largeur;
}
int Texture::getHauteur() const {
    return m_hauteur;
}
