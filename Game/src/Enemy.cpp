//
// Created by JEDREK on 23.04.2024.
//

#include "Enemy.h"
Enemy::Enemy(){
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, 2);
    speed = 0.8+distribution(generator)*0.1;
}

double Enemy::getSpriteHeight() //
{
    return enemySprite.getGlobalBounds().height;
}

double Enemy::getSpriteWidth() //
{
    return enemySprite.getGlobalBounds().width;
}

void Enemy::shoot(double direction)
{
    enemyProjectiles.emplace_back(x,y+getSpriteHeight()/2,direction); // prawo - 0, dol - 90, lewo - 180, gora - 270
}
std::vector<EnemyProjectile>& Enemy::getEnemyProjectiles()
{
    return enemyProjectiles;
}

double Enemy::getDirection() const
{
    return -atan2(y-Player::getY(),x-Player::getX())*180/M_PI+180;
}

bool Enemy::isShot()
{
    for(Projectile& projectile : Player::getProjectiles())
        if(projectile.getProjectileSprite().getGlobalBounds().intersects(enemySprite.getGlobalBounds()))
        {
            projectile.destroy();
            return true;
        }
    return false;
}

void Enemy::die(sf::RenderWindow &window)
{
    if(!toDie&&canSpawnCollectable) {
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(0, 1);

        if (distribution(generator) == 0 || Player::getClass()==4) {
            if (enemySprite.getScale().x > 0)
                CollectableVector::add(x + getSpriteWidth() / 2, y + getSpriteHeight() / 2, true);
            else
                CollectableVector::add(x - getSpriteWidth() / 2, y + getSpriteHeight() / 2, true);
        }
    }
    toDie= true;
    if(!isDead)
    {
        timer++;
        if(timer%15==0) {
            enemySprite.setTexture(deathTextures[currentTexture++]);
            enemySprite.setPosition(enemySprite.getPosition().x+1,enemySprite.getPosition().y-2);
            if(currentTexture>3)
                enemySprite.setPosition(enemySprite.getPosition().x-2,enemySprite.getPosition().y-1);
        }
        if(currentTexture==deathTextures.size())
        {
            enemySprite.setPosition(-100,-100);// do poprawy
            isDead= true;
        }
        enemySprite.setTextureRect(
                sf::IntRect(0, 0, enemySprite.getTexture()->getSize().x, enemySprite.getTexture()->getSize().y));
        window.draw(enemySprite);
    }

}

void Enemy::lookLeft()
{
    if(enemySprite.getScale().x>0) {
        enemySprite.setScale(-fabs(enemySprite.getScale().x), enemySprite.getScale().y);
        x+=getSpriteWidth();
        enemySprite.setPosition(x,y);
        helperSprite.setPosition(x,y);
        isLookingRight=false;
        helperSprite.setScale(-fabs(helperSprite.getScale().x),helperSprite.getScale().y);
    }
}

void Enemy::lookRight()
{
    if(enemySprite.getScale().x<0) {
        enemySprite.setScale(fabs(enemySprite.getScale().x), enemySprite.getScale().y);
        x-=getSpriteWidth();
        enemySprite.setPosition(x,y);
        helperSprite.setPosition(x,y);
        isLookingRight=true;
        helperSprite.setScale(fabs(helperSprite.getScale().x),helperSprite.getScale().y);
    }
}
void Enemy::update(sf::RenderWindow& window){
};
void Enemy::draw(sf::RenderWindow& window){
    window.draw(enemySprite);
};
void Enemy::buyReduceEnemySpeed(double reduce)
{
    speed=speed*reduce;
}

bool Enemy::getIsDead()
{
    return isDead;
}

void Enemy::resetStatics()
{
    enemyProjectiles.clear();
}
