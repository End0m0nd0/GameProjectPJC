//
// Created by JEDREK on 29.04.2024.
//

#include "EnemyProjectile.h"
EnemyProjectile::EnemyProjectile(double x, double y,double direction) : x(x), y(y), direction(direction)
{
    for(int i=0;i<4;i++)
        enemyProjectileTextures.push_back(sf::Texture());
    enemyProjectileTextures[0].loadFromFile("Sprites/Enemies/EnemyProjectile/EnemyProjectileOne.png");
    enemyProjectileTextures[1].loadFromFile("Sprites/Enemies/EnemyProjectile/EnemyProjectileTwo.png");
    enemyProjectileTextures[2].loadFromFile("Sprites/Enemies/EnemyProjectile/EnemyProjectileThree.png");
    enemyProjectileTextures[3].loadFromFile("Sprites/Enemies/EnemyProjectile/EnemyProjectileFour.png");
    enemyProjectileSprite.setTexture(enemyProjectileTextures[0]);
    enemyProjectileSprite.setPosition(x,y);
}

void EnemyProjectile::update(sf::RenderWindow& window) {
    if(isActive) {
        timer++;
        if (timer % 10 == 0) {
            enemyProjectileSprite.setTexture(enemyProjectileTextures[currentTexture++]);
            if (currentTexture == enemyProjectileTextures.size())
                currentTexture = 0;
        }

        x += cos(direction * M_PI / 180) * speed;
        y += -sin(direction * M_PI / 180) * speed;

        enemyProjectileSprite.setPosition(x, y);

        if (isTouchingPlayer()) {
            isActive = false;
            x = -100;
            y = -100;
            enemyProjectileSprite.setPosition(x,y);
            Player::gotShot();
        }

        window.draw(enemyProjectileSprite);
    }
}

bool EnemyProjectile::isTouchingPlayer()
{
    return enemyProjectileSprite.getGlobalBounds().intersects(Player::player().getGlobalBounds());
}


void EnemyProjectile::draw(sf::RenderWindow& window){
    window.draw(enemyProjectileSprite);
}

bool EnemyProjectile::canBuyReduceBulletSpeed()
{
    return speed * 0.93 > 0.7;
}
void EnemyProjectile::buyReduceBulletSpeed()
{
    speed=speed*0.93;
}

double EnemyProjectile::getX() const
{
    return x;
}

double EnemyProjectile::getY() const
{
    return y;
}

void EnemyProjectile::resetStatics()
{
    speed=1;
}
