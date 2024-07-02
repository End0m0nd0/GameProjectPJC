
#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
//#include "Stage.h"
//#include "Map.h"
#include "Projectile.h"
#include "Directions.h"

class Player  {
private:
    static inline int chosenClass=0; // 1 - berserk, 2-sprinter, 3-devastator, 4- lucky man
    static inline bool isDead= false;
    static inline bool toDie=false;
    static inline int reloadTime=13;
    static inline double speed=1;
    double playerSize=1.25;
    bool isCurrentlyShooting=false;
    int timer=0;
    int currentRunFrame=0;
    int currentShootFrame=0;
    int currentDeathFrame=0;
    static inline int health=3;
    static inline int maxHealth=3;
    static inline int coins=5;
    static inline int stagesCleared=0;
    sf::Texture playerTexture;
    static inline sf::Sprite playerSprite;
    sf::Texture playerRunTexture[4];
    sf::Texture playerShootTexture[4];
    sf::Texture playerDeathTexture[7];
    static inline double x;
    static inline double y;
    static inline std::vector<Projectile> projectiles;

public:
    static sf::Sprite& player();
    Player();
    void update(Stage& stage);
    void shoot();
    static double getX();
    static double getY();
    bool getIsCurrentlyShooting() const;
    static double getSpriteHeight();
    static double getSpriteWidth();
    static std::vector<Projectile>& getProjectiles();
    static void add(Projectile projectile);
    static void gotShot();
    static int getHealth();
    static int getMaxHealth();
    void lookLeft();
    void lookRight();
    static void collectCoin();
    static void collectDoubleCoin();
    static void collectHealth();
    static void collectMaxHealth();
    static int getCoins();
    static int getStagesCleared();
    static void stageCleared();
    static void draw(sf::RenderWindow& window);
    static void buy(int x);
    static bool canBuyReloadTime();
    static void buyReloadTime();
    static bool canBuyIncreaseSpeed();
    static void buyIncreaseSpeed();
    static bool canBuyHeal();
    static bool getIsDead();
    static void cheat();
    static void setClass(int x);
    static int getClass();
    static void resetStatics();
};



#endif //UNTITLED_PLAYER_H
