//
// Created by JEDREK on 18.04.2024.
//

#include "Projectile.h"
#include "Path.h"

Projectile::Projectile(double x,double y,int direction) : x(x),y(y),direction(direction)
{
    for(int i=0;i<4;i++)
        ProjectileTextures.push_back(sf::Texture());
    ProjectileTextures[0].loadFromFile(Path::get()+"Sprites/PlayerSprites/Projectile/ProjectileOne.png");
    ProjectileTextures[1].loadFromFile(Path::get()+"Sprites/PlayerSprites/Projectile/ProjectileTwo.png");
    ProjectileTextures[2].loadFromFile(Path::get()+"Sprites/PlayerSprites/Projectile/ProjectileThree.png");
    ProjectileTextures[3].loadFromFile(Path::get()+"Sprites/PlayerSprites/Projectile/ProjectileFour.png");
    projecitleSprite.setTexture(ProjectileTextures[0]);
    projecitleSprite.setPosition(x,y);
}

void Projectile::update(sf::RenderWindow& window)
{
    if(isActive) {
        timer++;
        if (timer % 10 == 0) {
            projecitleSprite.setTexture(ProjectileTextures[currentTexture++]);
            if (currentTexture == ProjectileTextures.size())
                currentTexture = 0;
        }

        if (direction == 1) x -= speed;
        if (direction == 2) y -= speed;
        if (direction == 3) x += speed;
        if (direction == 4) y += speed;
        projecitleSprite.setPosition(x, y);
    }
    projecitleSprite.setTexture(ProjectileTextures[currentTexture]);
    window.draw(projecitleSprite);
}

sf::Sprite Projectile::projectile()
{
    return projecitleSprite;
}

double Projectile::getY()
{
    return y;
}
double Projectile::getX()
{
    return x;
}

double Projectile::getXCenter() //
{
    return x+projecitleSprite.getGlobalBounds().width/2;  //zwraca wysokość Sprite'a
}

double Projectile::getYCenter()
{
    return y+projecitleSprite.getGlobalBounds().height/2;  //zwraca szerokosc Sprite'a
}

//bool Projectile::operator==(const Projectile& other) const {
//    return x == other.x && y == other.y&&timer==other.timer;
//}

void Projectile::destroy() // w playerze usuwane z pamieci
{
    x=-1000;
    y=-1000;
    projecitleSprite.setPosition(x,y);
}

sf::Sprite& Projectile::getProjectileSprite()
{
    return projecitleSprite;
}

void Projectile::draw(sf::RenderWindow& window){
    window.draw(projecitleSprite);
}
