
#ifndef UNTITLED_PROJECTILE_H
#define UNTITLED_PROJECTILE_H


#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile {
private:
    double speed =3;
    std::vector<sf::Texture> ProjectileTextures;
    sf::Sprite projecitleSprite;
    bool right;
    double x;
    double y;
    int direction;
    int timer=0;
    int currentTexture=0;
    bool isActive=true;

public:

    Projectile(double x,double y,int direction);
    void update(sf::RenderWindow& window);
    sf::Sprite projectile();
    double getY();
    double getX();
    double getXCenter();
    double getYCenter();
 //   bool operator==(const Projectile& other) const;
    void destroy();
    sf::Sprite& getProjectileSprite();
    void draw(sf::RenderWindow& window);
};


#endif //UNTITLED_PROJECTILE_H
