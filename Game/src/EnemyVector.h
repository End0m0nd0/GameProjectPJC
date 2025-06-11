//
// Created by Mirek N on 01.05.2024.
//

#ifndef UNTITLED_ENEMYVECTOR_H
#define UNTITLED_ENEMYVECTOR_H

#include <memory>
#include "Map.h"
#include "FlyingEnemy.h"
#include "Turret.h"
#include "map"
#include "random"
#include "HumanEnemy.h"
#include "RobotEnemy.h"

class EnemyVector {
private:
    static inline std::map<int,std::vector<std::unique_ptr<Enemy>>> mapa;
public:
    EnemyVector();
    void createNew();
    void updateFlying(sf::RenderWindow& window);
    void updateWalking(sf::RenderWindow& window);
    void check();
    void draw(sf::RenderWindow& window);
    static void buyReduceEnemySpeed(double reduce);
    static void resetStatics();

};


#endif //UNTITLED_ENEMYVECTOR_H
