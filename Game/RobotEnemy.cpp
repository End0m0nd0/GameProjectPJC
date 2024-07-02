//
// Created by JEDREK on 12.05.2024.
//

#include "RobotEnemy.h"
RobotEnemy::RobotEnemy(double x, double y) {
    this->x = x;
    this->y = y;
    health=7;
    helperSprite.setPosition(x,y);
    speed=speed*1.3;
    enemySprite.setPosition(x, y);
    for (int i = 0; i < 4; i++) {
        activateTextures.push_back(sf::Texture());
        shootTextures.push_back(sf::Texture());
        runTextures.push_back(sf::Texture());
        deathTextures.push_back(sf::Texture());
        idleTextures.push_back(sf::Texture());
    }
    activateTextures.push_back(sf::Texture());
    for (int i = 0; i < 4; i++)
        deathTextures.push_back(sf::Texture());
    beforeActivation.loadFromFile("Sprites/Enemies/Robot/BeforeActivation/BeforeActivation.png");
    activateTextures[0].loadFromFile("Sprites/Enemies/Robot/Activate/ActivateOne.png");
    activateTextures[1].loadFromFile("Sprites/Enemies/Robot/Activate/ActivateTwo.png");
    activateTextures[2].loadFromFile("Sprites/Enemies/Robot/Activate/ActivateThree.png");
    activateTextures[3].loadFromFile("Sprites/Enemies/Robot/Activate/ActivateFour.png");
    activateTextures[4].loadFromFile("Sprites/Enemies/Robot/Activate/ActivateFive.png");
    idleTextures[0].loadFromFile("Sprites/Enemies/Robot/Idle/IdleOne.png");
    idleTextures[1].loadFromFile("Sprites/Enemies/Robot/Idle/IdleTwo.png");
    idleTextures[2].loadFromFile("Sprites/Enemies/Robot/Idle/IdleThree.png");
    idleTextures[3].loadFromFile("Sprites/Enemies/Robot/Idle/IdleFour.png");
    runTextures[0].loadFromFile("Sprites/Enemies/Robot/Run/RunOne.png");
    runTextures[1].loadFromFile("Sprites/Enemies/Robot/Run/RunTwo.png");
    runTextures[2].loadFromFile("Sprites/Enemies/Robot/Run/RunThree.png");
    runTextures[3].loadFromFile("Sprites/Enemies/Robot/Run/RunFour.png");
    shootTextures[0].loadFromFile("Sprites/Enemies/Robot/Shoot/ShootOne.png");
    shootTextures[1].loadFromFile("Sprites/Enemies/Robot/Shoot/ShootTwo.png");
    shootTextures[2].loadFromFile("Sprites/Enemies/Robot/Shoot/ShootThree.png");
    shootTextures[3].loadFromFile("Sprites/Enemies/Robot/Shoot/ShootFour.png");
    deathTextures[0].loadFromFile("Sprites/Enemies/Robot/Death/DeathOne.png");
    deathTextures[1].loadFromFile("Sprites/Enemies/Robot/Death/DeathTwo.png");
    deathTextures[2].loadFromFile("Sprites/Enemies/Robot/Death/DeathThree.png");
    deathTextures[3].loadFromFile("Sprites/Enemies/Robot/Death/DeathFour.png");
    deathTextures[4].loadFromFile("Sprites/Enemies/Robot/Death/DeathFive.png");
    deathTextures[5].loadFromFile("Sprites/Enemies/Robot/Death/DeathSix.png");
    deathTextures[6].loadFromFile("Sprites/Enemies/Robot/Death/DeathSeven.png");
    deathTextures[7].loadFromFile("Sprites/Enemies/Robot/Death/DeathEight.png");
    enemySprite.setTexture(beforeActivation);
    helperSprite.setTexture(beforeActivation);
    enemySprite.setScale(0.8,0.8);
}

void RobotEnemy::update(sf::RenderWindow& window)
{
    timer++;
    if(!toActivate){
        if(rand()%200==0) toActivate=true;
    }
    if(toActivate&&!isActivated)
    {
        if (currentTexture >= activateTextures.size())
        {
            currentTexture=0;
            isActivated=true;
        }
        if(timer%30==0)
            enemySprite.setTexture(activateTextures[currentTexture++]);
    }
    if(isActive&&isActivated) {
        helperSprite.setPosition(enemySprite.getPosition());

        enemySprite.setPosition(x, y);
        if (Player::getX() < x - getSpriteWidth() && isLookingRight && !isRunning) {
            lookLeft();
            enemySprite.setPosition(x, y);
            isLookingRight = false;
        } else if (Player::getX() > x + getSpriteWidth() && !isLookingRight && !isRunning) {
            lookRight();
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
            //   shoot(getDirection());
        }
        if (isShooting && timer % 15 == 0) {
            if (currentTexture >= shootTextures.size()) {
                counter++;
                currentTexture = 0;
                isShooting = false;
            }
            enemySprite.setTexture(shootTextures[currentTexture++]);
            if(currentTexture==2)shoot(getDirection());
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
            checkDirection();
        }
        if(isRunning)
        {
            switch (direction) {
                case 1:
                    lookLeft();
                    if(Directions::canMoveLeft(helperSprite))
                        x-=speed*0.5;
                    break;
                case 2:
                    if(Directions::canMoveUp(helperSprite))
                        y-=speed*0.5;
                    break;
                case 3:
                    lookRight();
                    if(Directions::canMoveRight(helperSprite))
                        x+=speed*0.5;
                    break;
                case 4:
                    if(Directions::canMoveDown(helperSprite))
                        y+=speed*0.5;
                    break;
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
    }
    else if(isActivated)die(window);
    enemySprite.setTextureRect(
            sf::IntRect(0, 0, enemySprite.getTexture()->getSize().x, enemySprite.getTexture()->getSize().y));
    window.draw(enemySprite);
}

void RobotEnemy::checkDirection()
{
    if (fabs(x - Player::getX()) < fabs(y - Player::getY())) // gora dol
    {
        if (Player::getY() > y) //dol
        {
            if (Directions::canMoveDown(helperSprite)) direction = 4;
            else if (Directions::canMoveLeft(helperSprite)) direction = 1;
            else if (Directions::canMoveRight(helperSprite)) direction=3;
            else direction=2;
        }

        else // gora
        {
            if (Directions::canMoveUp(helperSprite)) direction = 2;
            else if (Directions::canMoveRight(helperSprite)) direction = 3;
            else if(Directions::canMoveLeft(helperSprite)) direction=1;
            else direction=4;
        }
    }

    else // lewo prawo // cos nie tak
    {
        if (Player::getX() > x) // prawo
        {
            if (Directions::canMoveRight(helperSprite)) direction = 3;
            else if (Directions::canMoveDown(helperSprite)) direction = 4;
            else if (Directions::canMoveUp(helperSprite)) direction = 2;
            else direction = 1;
        }

        else  // lewo
        {
            if (Directions::canMoveLeft(helperSprite)) direction = 1;
            else if (Directions::canMoveUp(helperSprite)) direction = 2;
            else if (Directions::canMoveDown(helperSprite)) direction = 4;
            else direction = 3;
        }
    }
    if (x == Player::getX() && y == Player::getY())
        direction=0;
}
