//
// Created by Mirek N on 01.05.2024.
//

#ifndef UNTITLED_TURRET_H
#define UNTITLED_TURRET_H
#pragma once
#include "Enemy.h"

class Turret : public Enemy{
private:
int timer=0;
int currentTexture=0;
public:
    Turret(double x, double y);
    void update(sf::RenderWindow& window) override;
};


#endif //UNTITLED_TURRET_H
