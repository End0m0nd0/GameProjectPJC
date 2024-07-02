//
// Created by JEDREK on 19.04.2024.
//

#ifndef UNTITLED_STAGE_H
#define UNTITLED_STAGE_H

#include "Background.h"
#include "Obstacle.h"
#include <vector>
#include <random>
#include <memory>

class Stage {
private:
    bool isCleared=false;
    Background bg;
    int design;

public:
    std::vector<Obstacle> vec;
    int obstacles[8][8];  //0 - nic   1 - komputer,  2 - reaktor,  3 - kwas,  4 - skrzynie,  5 - reaktor pusty
    Stage (bool firstStage=false);
    void drawBg(sf::RenderWindow& window);
    void updateOb(sf::RenderWindow& window);
    void drawOb(sf::RenderWindow& window);
    bool getIsCleared();
    void clear();
};


#endif //UNTITLED_STAGE_H