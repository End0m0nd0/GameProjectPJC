//
// Created by JEDREK on 07.05.2024.
//

#ifndef UNTITLED_HUMANENEMY_H
#define UNTITLED_HUMANENEMY_H

#include "Enemy.h"
#include "Directions.h"

class HumanEnemy : public Enemy {
private:
    bool isShooting = false;
    bool isRunning = false;
    int counter = 0;
    int direction; //1-lewo 2-gora 3-prawo 4-dol
public:
    HumanEnemy(double x, double y);
    void update(sf::RenderWindow& window) override;
    void checkDirection();

};


#endif //UNTITLED_HUMANENEMY_H
