//
// Created by JEDREK on 07.05.2024.
//

#ifndef UNTITLED_DIRECTIONS_H
#define UNTITLED_DIRECTIONS_H
#include "Map.h"

class Directions {
public:
    static bool canMoveLeft(sf::Sprite& sprite);
    static bool canMoveRight(sf::Sprite& sprite);
    static bool canMoveDown(sf::Sprite& sprite);
    static bool canMoveUp(sf::Sprite& sprite);
};


#endif //UNTITLED_DIRECTIONS_H
