//
// Created by JEDREK on 19.04.2024.
//

#ifndef UNTITLED_BACKGROUND_H
#define UNTITLED_BACKGROUND_H
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
class Background {
private:
    static int const rows=10;
    static int const columns=10;
    sf::Sprite floorSprites[rows][columns] ;
    int floorSpritesTextureNumber[rows][columns];
    sf::Texture textures[5];
public:
    Background();
    void draw(sf::RenderWindow& window);
    void renderNew();
};



#endif //UNTITLED_BACKGROUND_H