//
// Created by JEDREK on 24.05.2024.
//

#ifndef UNTITLED_COLLECTITEM_H
#define UNTITLED_COLLECTITEM_H
#include "SFML/Graphics.hpp"
#include "Player.h"

class CollectItem { // 1 - dodadkowe max zycie, 2 - zycie, 3 - coin, 4 - double coin
private :
    double x;
    double y;
    double startY;
    int id;
    sf::Sprite sprite;
    sf::Texture texture;
    bool isCollected=false;
    bool canBeCollected=false;
public :
    CollectItem(double x, double y,bool canBeCollected);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};


#endif //UNTITLED_COLLECTITEM_H
