//
// Created by JEDREK on 29.04.2024.
//

#ifndef UNTITLED_ENEMYPROJECTILE_H
#define UNTITLED_ENEMYPROJECTILE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "Player.h"


class EnemyProjectile {
private:
    bool isActive= true;
    double x;
    double y;
    double direction;
    sf::Sprite enemyProjectileSprite;
    std::vector<sf::Texture> enemyProjectileTextures;
    int currentTexture=0;
    int timer=0;
    static inline double speed=1;


public:
    EnemyProjectile(double x, double y,double direction);
    void update(sf::RenderWindow& window);
    bool isTouchingPlayer();
    void draw(sf::RenderWindow& window);
    static bool canBuyReduceBulletSpeed();
    static void buyReduceBulletSpeed();
    double getX() const;
    double getY() const;
    static void resetStatics();
};


#endif //UNTITLED_ENEMYPROJECTILE_H
