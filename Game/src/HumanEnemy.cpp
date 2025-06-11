//
// Created by JEDREK on 07.05.2024.
//

#include "HumanEnemy.h"
#include "Path.h"

HumanEnemy::HumanEnemy(double x, double y) {
    this->x = x;
    this->y = y;
    health=6;
    helperSprite.setPosition(x,y);
    speed=speed*1.4;
    enemySprite.setPosition(x, y);
    for (int i = 0; i < 4; i++) {
        shootTextures.emplace_back();
        runTextures.emplace_back();
        if(i<3)idleTextures.emplace_back();
        deathTextures.emplace_back();
    }
    for (int i = 0; i < 5; i++)
        deathTextures.emplace_back();
    runTextures[0].loadFromFile(Path::get()+"Sprites/Enemies/Human/Run/RunOne.png");
    runTextures[1].loadFromFile(Path::get()+"Sprites/Enemies/Human/Run/RunTwo.png");
    runTextures[2].loadFromFile(Path::get()+"Sprites/Enemies/Human/Run/RunThree.png");
    runTextures[3].loadFromFile(Path::get()+"Sprites/Enemies/Human/Run/RunFour.png");
    shootTextures[0].loadFromFile(Path::get()+"Sprites/Enemies/Human/Shoot/ShootOne.png");
    shootTextures[1].loadFromFile(Path::get()+"Sprites/Enemies/Human/Shoot/ShootTwo.png");
    shootTextures[2].loadFromFile(Path::get()+"Sprites/Enemies/Human/Shoot/ShootThree.png");
    shootTextures[3].loadFromFile(Path::get()+"Sprites/Enemies/Human/Shoot/ShootFour.png");
    idleTextures[0].loadFromFile(Path::get()+"Sprites/Enemies/Human/Idle/IdleOne.png");
    idleTextures[1].loadFromFile(Path::get()+"Sprites/Enemies/Human/Idle/IdleTwo.png");
    idleTextures[2].loadFromFile(Path::get()+"Sprites/Enemies/Human/Idle/IdleThree.png");
    deathTextures[0].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathOne.png");
    deathTextures[1].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathTwo.png");
    deathTextures[2].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathThree.png");
    deathTextures[3].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathFour.png");
    deathTextures[4].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathFive.png");
    deathTextures[5].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathSix.png");
    deathTextures[6].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathSeven.png");
    deathTextures[7].loadFromFile(Path::get()+"Sprites/Enemies/Human/Death/DeathEight.png");
    enemySprite.setTexture(idleTextures[0]);
    helperSprite.setTexture(idleTextures[0]);
    counter = rand() % 10;
}

void HumanEnemy::update(sf::RenderWindow& window)
{
    timer++;
    if(isActive) {
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
        enemySprite.setTextureRect(
                sf::IntRect(0, 0, enemySprite.getTexture()->getSize().x, enemySprite.getTexture()->getSize().y));
        window.draw(enemySprite);
    }
    else die(window);
}

void HumanEnemy::checkDirection()
{
    if (fabs(x - Player::getX()) < fabs(y - Player::getY())) // gora dol
    {
        if (Player::getY() > y) //dol
        {
            if (Directions::canMoveDown(helperSprite)) direction = 4;
            else if (Directions::canMoveRight(helperSprite)) direction = 3;
            else if (Directions::canMoveLeft(helperSprite)) direction=1;
            else direction=2;
        }

        else // gora
        {
            if (Directions::canMoveUp(helperSprite)) direction = 2;
            else if (Directions::canMoveLeft(helperSprite)) direction = 1;
            else if(Directions::canMoveRight(helperSprite)) direction=3;
            else direction=4;
        }
    }

    else // lewo prawo // cos nie tak
    {
        if (Player::getX() > x) // prawo
        {
            if (Directions::canMoveRight(helperSprite)) direction = 3;
            else if (Directions::canMoveUp(helperSprite)) direction = 2;
            else if (Directions::canMoveDown(helperSprite)) direction = 4;
            else direction = 1;
        }

        else  // lewo
        {
            if (Directions::canMoveLeft(helperSprite)) direction = 1;
            else if (Directions::canMoveDown(helperSprite)) direction = 4;
            else if (Directions::canMoveUp(helperSprite)) direction = 2;
            else direction = 3;
        }
    }
    if (x == Player::getX() && y == Player::getY())
        direction=0;
}
