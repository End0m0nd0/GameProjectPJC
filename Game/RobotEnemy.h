//
// Created by JEDREK on 07.05.2024.
//

#ifndef UNTITLED_ROBOTENEMY_H
#define UNTITLED_ROBOTENEMY_H

#include "Enemy.h"
#include "Directions.h"

class RobotEnemy : public Enemy {
private:
    bool isActivated=false;
    bool toActivate=false;
    bool isShooting = false;
    bool isRunning = false;
    int counter = 0;
    int direction; //1-lewo 2-gora 3-prawo 4-dol
    sf::Texture beforeActivation;
    std::vector<sf::Texture> activateTextures;
public:
    RobotEnemy(double x, double y);
    void update(sf::RenderWindow& window) override;
    void checkDirection();
};


#endif //UNTITLED_ROBOTENEMY_H
