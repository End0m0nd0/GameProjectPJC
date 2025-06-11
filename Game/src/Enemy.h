//
// Created by JEDREK on 23.04.2024.
//

#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "EnemyProjectile.h"
#include <cmath>
#include "CollectableVector.h"

class Enemy {
protected:
    bool isActive=true;
    bool isDead=false;
    bool toDie=false;
    bool canSpawnCollectable= true;
    bool isLookingRight=true;
    double health=5;
    double speed=1;
    double x=0;
    double y=0;
    int timer=0;
    int currentTexture=0;
    sf::Sprite enemySprite;
    sf::Sprite helperSprite;  // do sprawdzania czy moze sie ruszyc w danym kierunku ( animacje rozszerzaly sprite'a i robilo to problemy )
    std::vector<sf::Texture> runTextures;
    std::vector<sf::Texture> shootTextures;
    std::vector<sf::Texture> dieTextures;
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> deathTextures;
    static inline std::vector<EnemyProjectile> enemyProjectiles;
public:
    Enemy();
    double getSpriteHeight();
    double getSpriteWidth();
    void shoot(double direction);
    static std::vector<EnemyProjectile>& getEnemyProjectiles();
    double getDirection() const;
    bool isShot();
    void die(sf::RenderWindow &window);
    void lookLeft();
    void lookRight();
    virtual void update(sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window);
    virtual void buyReduceEnemySpeed(double reduce);
    virtual bool getIsDead();
    static void resetStatics();
};


#endif //UNTITLED_ENEMY_H
