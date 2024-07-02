//
// Created by JEDREK on 24.04.2024.
//

#include "FlyingEnemy.h"
FlyingEnemy::FlyingEnemy(double x, double y)
{
    this->x=x;
    this->y=y;
    health=5;
    canSpawnCollectable=false;
    enemySprite.setPosition(x,y);
    for(int i=0;i<4;i++)
    {
        shootTextures.emplace_back();
        runTextures.emplace_back();
        idleTextures.emplace_back();
        deathTextures.emplace_back();
    }
    for(int i=0;i<5;i++)
        deathTextures.emplace_back();
    runTextures[0].loadFromFile("Sprites/Enemies/Flying/Run/RunOne.png");
    runTextures[1].loadFromFile("Sprites/Enemies/Flying/Run/RunTwo.png");
    runTextures[2].loadFromFile("Sprites/Enemies/Flying/Run/RunThree.png");
    runTextures[3].loadFromFile("Sprites/Enemies/Flying/Run/RunFour.png");
    shootTextures[0].loadFromFile("Sprites/Enemies/Flying/Shoot/ShootOne.png");
    shootTextures[1].loadFromFile("Sprites/Enemies/Flying/Shoot/ShootTwo.png");
    shootTextures[2].loadFromFile("Sprites/Enemies/Flying/Shoot/ShootThree.png");
    shootTextures[3].loadFromFile("Sprites/Enemies/Flying/Shoot/ShootFour.png");
    idleTextures[0].loadFromFile("Sprites/Enemies/Flying/Idle/IdleOne.png");
    idleTextures[1].loadFromFile("Sprites/Enemies/Flying/Idle/IdleTwo.png");
    idleTextures[2].loadFromFile("Sprites/Enemies/Flying/Idle/IdleThree.png");
    idleTextures[3].loadFromFile("Sprites/Enemies/Flying/Idle/IdleFour.png");
    deathTextures[0].loadFromFile("Sprites/Enemies/Flying/Death/DeathOne.png");
    deathTextures[1].loadFromFile("Sprites/Enemies/Flying/Death/DeathTwo.png");
    deathTextures[2].loadFromFile("Sprites/Enemies/Flying/Death/DeathThree.png");
    deathTextures[3].loadFromFile("Sprites/Enemies/Flying/Death/DeathFour.png");
    deathTextures[4].loadFromFile("Sprites/Enemies/Flying/Death/DeathFive.png");
    deathTextures[5].loadFromFile("Sprites/Enemies/Flying/Death/DeathSix.png");
    deathTextures[6].loadFromFile("Sprites/Enemies/Flying/Death/DeathSeven.png");
    deathTextures[7].loadFromFile("Sprites/Enemies/Flying/Death/DeathEight.png");
    enemySprite.setTexture(idleTextures[0]);
    counter=rand()%10;
}

void FlyingEnemy::update(sf::RenderWindow& window)
{
    timer++;
    if(isActive) {

        enemySprite.setPosition(x, y);
        if (Player::getX() < x - getSpriteWidth() && isLookingRight) {
            enemySprite.setScale(-fabs(enemySprite.getScale().x), enemySprite.getScale().y);
            x += getSpriteWidth();
            enemySprite.setPosition(x, y);
            isLookingRight = false;
        } else if (Player::getX() > x + getSpriteWidth() && !isLookingRight) {
            enemySprite.setScale(fabs(enemySprite.getScale().x), enemySprite.getScale().y);
            x -= getSpriteWidth();
            enemySprite.setPosition(x, y);
            isLookingRight = true;
        }
        if (!isShooting && !isRunning && timer % 25 == 0 && (counter % 6 == 0 || counter % 6 == 1)) {
            if (currentTexture >= idleTextures.size()) {
                counter++;
                currentTexture = 0;
            }
            enemySprite.setTexture(idleTextures[currentTexture++]);
        }
        if (counter % 6 == 2) {
            isShooting = true;
        }
        if (isShooting && timer % 15 == 0) {
            if (currentTexture >= shootTextures.size()) {
                counter++;
                currentTexture = 0;
                isShooting = false;
            }
            enemySprite.setTexture(shootTextures[currentTexture++]);
            if (currentTexture % 2 == 1) shoot(getDirection());
        }

        if (counter % 6 == 3 || counter % 6 == 4 || counter % 6 == 5) {
            isRunning = true;
        }
        if (isRunning && timer % 15 == 0) {
            if (currentTexture >= runTextures.size()) {
                counter++;
                currentTexture = 0;
                isRunning = false;
            }
            enemySprite.setTexture(runTextures[currentTexture++]);
        }
        if (isRunning && x != Player::getX() && y != Player::getY()) {
            if (fabs(x - Player::getX()) < fabs(y - Player::getY())) {
                if (Player::getY() > y)y += speed * 0.5;
                else y -= speed * 0.5;
            } else {
                if (Player::getX() > x)x += speed * 0.5;
                else x -= speed * 0.5;
            }
        }

        bool gotShot = isShot();
        if (gotShot&&Player::getClass()!=3) health--;
        else if(gotShot) health-=2;
        if(health<=0) {
            isActive=false;
            currentTexture=0;
            timer=0;
        }
        enemySprite.setTextureRect(
                sf::IntRect(0, 0, enemySprite.getTexture()->getSize().x, enemySprite.getTexture()->getSize().y));
        window.draw(enemySprite);
    }
    else die(window);
}
