//
// Created by JEDREK on 18.04.2024.
//

#include "Player.h"
sf::Sprite& Player::player()
{
    return playerSprite;
}

Player::Player()
{
    playerSprite.setScale(playerSize,playerSize);
    playerTexture.loadFromFile("Sprites/PlayerSprites/PlayerSprite.png");
    playerSprite.setTexture(playerTexture);
    x=400-getSpriteWidth()/2;
    y=400-getSpriteHeight()/2;
    playerRunTexture[0].loadFromFile("Sprites/PlayerSprites/Run/PlayerRunOne.png");
    playerRunTexture[1].loadFromFile("Sprites/PlayerSprites/Run/PlayerRunTwo.png");
    playerRunTexture[2].loadFromFile("Sprites/PlayerSprites/Run/PlayerRunThree.png");
    playerRunTexture[3].loadFromFile("Sprites/PlayerSprites/Run/PlayerRunFour.png");
    playerShootTexture[0].loadFromFile("Sprites/PlayerSprites/Shoot/PlayerShootOne.png");
    playerShootTexture[1].loadFromFile("Sprites/PlayerSprites/Shoot/PlayerShootTwo.png");
    playerShootTexture[2].loadFromFile("Sprites/PlayerSprites/Shoot/PlayerShootThree.png");
    playerShootTexture[3].loadFromFile("Sprites/PlayerSprites/Shoot/PlayerShootFour.png");
    playerDeathTexture[0].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathOne.png");
    playerDeathTexture[1].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathTwo.png");
    playerDeathTexture[2].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathThree.png");
    playerDeathTexture[3].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathFour.png");
    playerDeathTexture[4].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathFive.png");
    playerDeathTexture[5].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathSix.png");
    playerDeathTexture[6].loadFromFile("Sprites/PlayerSprites/Death/PlayerDeathSeven.png");
}
void Player::update(Stage& stage)
{
    if(toDie){
    timer++;
    if(timer%20==0){
        playerSprite.setTexture(playerDeathTexture[currentDeathFrame++]);
        playerSprite.setPosition(playerSprite.getPosition().x-2.35f,playerSprite.getPosition().y-2.75f);
    }
        if(currentDeathFrame==7) {
            isDead = true;
            toDie = false;
            playerSprite.setTexture(playerTexture);
            playerSprite.setTextureRect(sf::IntRect(0, 0, playerTexture.getSize().x,
                                                    playerTexture.getSize().y));
        }
        else
            playerSprite.setTextureRect(sf::IntRect(0, 0, playerDeathTexture[currentDeathFrame-1].getSize().x,
                                                    playerDeathTexture[currentDeathFrame-1].getSize().y));

    }
    else {
        if (!isCurrentlyShooting) {
            playerSprite.setTexture(playerTexture);
            playerSprite.setTextureRect(sf::IntRect(0, 0, playerTexture.getSize().x, playerTexture.getSize().y));
            timer++;
            if (timer % 20 == 0)
                currentRunFrame++;
            if (currentRunFrame > 3) currentRunFrame = 0;
            playerSprite.setPosition(x, y);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                x - getSpriteWidth() > 0 && Directions::canMoveLeft(playerSprite)) {
                if (playerSprite.getScale().x > 0) x += getSpriteWidth();
                playerSprite.setTextureRect(sf::IntRect(0, 0, playerRunTexture[currentRunFrame].getSize().x,
                                                        playerRunTexture[currentRunFrame].getSize().y));
                playerSprite.setTexture(playerRunTexture[currentRunFrame]);
                playerSprite.setScale(-fabs(playerSprite.getScale().x), playerSprite.getScale().y);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    x -= speed * 1.25;
                else x -= speed * 1.4;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                x + getSpriteWidth() < 800 && Directions::canMoveRight(playerSprite)) {
                if (playerSprite.getScale().x < 0) x -= getSpriteWidth();
                playerSprite.setTexture(playerRunTexture[currentRunFrame]);
                playerSprite.setTextureRect(sf::IntRect(0, 0, playerRunTexture[currentRunFrame].getSize().x,
                                                        playerRunTexture[currentRunFrame].getSize().y));
                playerSprite.setScale(fabs(playerSprite.getScale().x), playerSprite.getScale().y);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    x += speed * 1.25;
                else x += speed * 1.4;

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y > 0 && Directions::canMoveUp(playerSprite)) {
                playerSprite.setTextureRect(sf::IntRect(0, 0, playerRunTexture[currentRunFrame].getSize().x,
                                                        playerRunTexture[currentRunFrame].getSize().y));
                playerSprite.setTexture(playerRunTexture[currentRunFrame]);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    y -= speed * 1.25;
                else y -= speed * 1.4;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y < 800 - getSpriteHeight() &&
                Directions::canMoveDown(playerSprite)) {
                playerSprite.setTextureRect(sf::IntRect(0, 0, playerRunTexture[currentRunFrame].getSize().x,
                                                        playerRunTexture[currentRunFrame].getSize().y));
                playerSprite.setTexture(playerRunTexture[currentRunFrame]);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    y += speed * 1.25;
                else y += speed * 1.4;
            }
            if (stage.getIsCleared()) {
                if (Map::getRight() && x + getSpriteWidth() > 800 && y > 320 && y + getSpriteHeight() < 480 &&
                    playerSprite.getScale().x > 0) {
                    x = 10;
                    Map::xAdd();
                } else if (Map::getLeft() && x - getSpriteWidth() < 0 && y > 320 && y + getSpriteHeight() < 480 &&
                           playerSprite.getScale().x < 0) {
                    x = 790;
                    Map::xSub();
                } else if (Map::getTop() && y < 0 &&
                           ((playerSprite.getScale().x > 0 && x > 320 && x + getSpriteWidth() < 480) ||
                            playerSprite.getScale().x < 0 && x - getSpriteWidth() > 320 && x < 480)) {
                    y = 790 - getSpriteHeight();
                    Map::ySub();
                } else if (Map::getBottom() && y + getSpriteHeight() > 800 &&
                           ((playerSprite.getScale().x > 0 && x > 320 && x + getSpriteWidth() < 480) ||
                            (playerSprite.getScale().x < 0 && x - getSpriteWidth() > 320 && x < 480))) {
                    y = 10;
                    Map::yAdd();
                }
            }

        } else {
            if (currentShootFrame == 4) {
                isCurrentlyShooting = false;
                currentShootFrame = 0;
                playerSprite.setTexture(playerTexture);
                timer = 0;
            }
            timer++;
            if (timer % reloadTime == 0) {
                playerSprite.setTexture(playerShootTexture[currentShootFrame]);
                playerSprite.setTextureRect(sf::IntRect(0, 0, playerShootTexture[currentShootFrame].getSize().x,
                                                        playerShootTexture[currentShootFrame].getSize().y));
                currentShootFrame++;
            }

        }
        if (health <= 0) {
            timer=0;
            currentDeathFrame=0;
            playerSprite.setTexture(playerDeathTexture[0]);
            lookRight();
            toDie = true;
        }
    }
}
void Player::shoot()
{
    isCurrentlyShooting=true;
}

double Player::getX()
{
    return x;
}

double Player::getY()
{
    return y;
}

bool Player::getIsCurrentlyShooting() const{
    return isCurrentlyShooting;
};

double Player::getSpriteHeight(){
    return playerSprite.getGlobalBounds().height;  //zwraca wysokość Sprite'a
}


double Player::getSpriteWidth()
{
    return playerSprite.getGlobalBounds().width;   //zwraca szerokość Sprite'a
}


std::vector<Projectile>& Player::getProjectiles()
{
    return projectiles;
}

void Player::add(Projectile projectile)
{
    projectiles.push_back(projectile);
}
void Player::gotShot()
{
    health--;
}
int Player::getHealth()
{
    return health;
}
int Player::getMaxHealth()
{
    return maxHealth;
}

void Player::lookLeft()
{
    if(playerSprite.getScale().x>0) {
        playerSprite.setScale(-fabs(playerSprite.getScale().x), playerSprite.getScale().y);
        x+=getSpriteWidth();
        playerSprite.setPosition(x,y);
    }
}

void Player::lookRight()
{
    if(playerSprite.getScale().x<0) {
        playerSprite.setScale(fabs(playerSprite.getScale().x), playerSprite.getScale().y);
        x-=getSpriteWidth();
        playerSprite.setPosition(x,y);
    }
}

void Player::collectCoin()
{
    coins++;
}

void Player::collectDoubleCoin()
{
    coins+=2;
}

void Player::collectHealth()
{
    if(maxHealth>health||chosenClass==1)health++;
}

void Player::collectMaxHealth()
{
    if(chosenClass!=1)maxHealth++;
    else collectHealth();
}

int Player::getCoins()
{
    return coins;
}

int Player::getStagesCleared(){
    return stagesCleared;
}
void Player::stageCleared()
{
    stagesCleared++;
}

void Player::draw(sf::RenderWindow& window){
    window.draw(playerSprite);
}

void Player::buy(int x)
{
    coins -=x;
}

bool Player::canBuyReloadTime()
{
    return reloadTime - 2 > 2;
}
void Player::buyReloadTime()
{
    reloadTime-=2;
}
bool Player::canBuyIncreaseSpeed()
{
    return (speed+0.05<=1.5||(speed+0.05<=2&&chosenClass==2));
}
void Player::buyIncreaseSpeed()
{
    speed+=0.05;
}

bool Player::canBuyHeal()
{
    return health<maxHealth||chosenClass==1;
}
bool Player::getIsDead()
{
    return isDead;
}

void Player::cheat(){
    coins+=10;
}

void Player::setClass(int x){
    chosenClass=x;
    if(x==1) maxHealth=0;
    if(x==2) speed=1.5;
}

int Player::getClass(){
    return chosenClass;
}

void Player::resetStatics()
{
    isDead= false;
    toDie= false;
    chosenClass=0;
    reloadTime=13;
    speed=1;
    health=3;
    maxHealth=3;
    coins=5;
    stagesCleared=0;
    playerSprite.setScale(fabs(playerSprite.getScale().x),playerSprite.getScale().y);
    x=400-getSpriteWidth()/2;
    y=400-getSpriteHeight()/2;
    playerSprite.setPosition(x,y);
    projectiles.clear();
}
