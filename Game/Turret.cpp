//
// Created by Mirek N on 01.05.2024.
//

#include "Turret.h"
Turret::Turret(double x, double y)
{
    this->x=x;
    this->y=y;
    health=4;
    for(int i=0;i<16;i++)
        shootTextures.push_back(sf::Texture());
    for(int i=0;i<8;i++)
        deathTextures.push_back(sf::Texture());
    shootTextures[0].loadFromFile("Sprites/Enemies/Turret/Shoot/LeftShootOne.png");
    shootTextures[1].loadFromFile("Sprites/Enemies/Turret/Shoot/LeftShootTwo.png");
    shootTextures[2].loadFromFile("Sprites/Enemies/Turret/Shoot/LeftShootThree.png");
    shootTextures[3].loadFromFile("Sprites/Enemies/Turret/Shoot/LeftShootFour.png");
    shootTextures[4].loadFromFile("Sprites/Enemies/Turret/Shoot/UpShootOne.png");
    shootTextures[5].loadFromFile("Sprites/Enemies/Turret/Shoot/UpShootTwo.png");
    shootTextures[6].loadFromFile("Sprites/Enemies/Turret/Shoot/UpShootThree.png");
    shootTextures[7].loadFromFile("Sprites/Enemies/Turret/Shoot/UpShootFour.png");
    shootTextures[8].loadFromFile("Sprites/Enemies/Turret/Shoot/RightShootOne.png");
    shootTextures[9].loadFromFile("Sprites/Enemies/Turret/Shoot/RightShootTwo.png");
    shootTextures[10].loadFromFile("Sprites/Enemies/Turret/Shoot/RightShootThree.png");
    shootTextures[11].loadFromFile("Sprites/Enemies/Turret/Shoot/RightShootFour.png");
    shootTextures[12].loadFromFile("Sprites/Enemies/Turret/Shoot/DownShootOne.png");
    shootTextures[13].loadFromFile("Sprites/Enemies/Turret/Shoot/DownShootTwo.png");
    shootTextures[14].loadFromFile("Sprites/Enemies/Turret/Shoot/DownShootThree.png");
    shootTextures[15].loadFromFile("Sprites/Enemies/Turret/Shoot/DownShootFour.png");
    deathTextures[0].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathOne.png");
    deathTextures[1].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathTwo.png");
    deathTextures[2].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathThree.png");
    deathTextures[3].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathFour.png");
    deathTextures[4].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathFive.png");
    deathTextures[5].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathSix.png");
    deathTextures[6].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathSeven.png");
    deathTextures[7].loadFromFile("Sprites/Enemies/Turret/Death/TurretDeathEight.png");
    enemySprite.setTexture(shootTextures[0]);
    enemySprite.setPosition(x,y);
    currentTexture=rand()%15;
}
void Turret::update(sf::RenderWindow& window)
{
    timer++;
    if(isActive) {
        enemySprite.setPosition(x, y);
        if (timer % 20 == 0) {
            enemySprite.setTexture(shootTextures[currentTexture++]);

            if (currentTexture == 1) shoot(180);
            if (currentTexture == 5) shoot(90);
            if (currentTexture == 9) shoot(0);
            if (currentTexture == 13) shoot(-90);
        }
        if (currentTexture == shootTextures.size())
            currentTexture = 0;

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
