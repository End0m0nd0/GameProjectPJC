//
// Created by JEDREK on 30.04.2024.
//

#ifndef UNTITLED_HEALTHBAR_H
#define UNTITLED_HEALTHBAR_H

#include "Player.h"
class HealthBar {
private:
    sf::Sprite emptySprite;
    sf::Texture emptyTexture;
    sf::Sprite fullSprite;
    sf::Texture fullTexture;

    sf::Sprite coinSprite;
    sf::Texture coinTexture;
public:
    HealthBar();
    void Update(sf::RenderWindow& window);
};


#endif //UNTITLED_HEALTHBAR_H
