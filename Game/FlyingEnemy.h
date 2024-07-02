//
// Created by JEDREK on 24.04.2024.
//

#ifndef UNTITLED_FLYINGENEMY_H
#define UNTITLED_FLYINGENEMY_H

#include "Enemy.h"

class FlyingEnemy : public Enemy{
private:
    bool isLookingRight=true;
    bool isShooting=false;
    bool isRunning=false;
    int counter=0;
public:
    FlyingEnemy(double x, double y);
    void update(sf::RenderWindow& window) override;


};


#endif //UNTITLED_FLYINGENEMY_H
