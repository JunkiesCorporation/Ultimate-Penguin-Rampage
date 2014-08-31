#ifndef ANIMATION_H
#define ANIMATION_H

#include "Enums.h"
#include "Texture.h"

class Animation
{
    public:
        Animation(); ///< Constructeur par défaut
        Animation(std::string cheminFichier); ///< Constructeur à partir d'un fichier

        ~Animation(); ///< Destructeur

        void update();
        void render(int x, int y);
    protected:
    private:
        void charger(std::string cheminFichier);

        int m_nombreImages;
        int m_imageActuelle;
        int m_vitesseAnimation;

        Direction m_direction; ///< La direction de l'Animation

        Texture m_plancheSprites; ///< L'image contenant les images de l'Animation
};

#endif // ANIMATION_H
