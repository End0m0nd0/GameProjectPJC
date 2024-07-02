//
// Created by JEDREK on 21.04.2024.
//

#ifndef UNTITLED_OBSTACLE_H
#define UNTITLED_OBSTACLE_H
#include <SFML/Graphics.hpp>

class Obstacle {
private:
    double x;
    double y;
    int id;
    sf::Sprite obstacleSprite;
    std::vector<sf::Texture> texture;
    int currentTexture=0;
    int timer=0;


    bool isChest = false;
    bool opened=false;
    sf::Sprite  playerSprite;

public:
    Obstacle(int id, double x, double y);
    void draw(sf::RenderWindow &window);
    bool open(sf::Sprite&  playerSprite);
    void update();
    double getX() const;
    double getY() const;

};
#endif //UNTITLED_OBSTACLE_H
