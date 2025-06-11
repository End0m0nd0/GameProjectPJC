//
// Created by Mirek N on 01.05.2024.
//

#include "EnemyVector.h"
EnemyVector::EnemyVector() {
    createNew();
}

void EnemyVector::createNew()
{
    mapa.clear();
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> enemies(0, 3);
    std::uniform_int_distribution<int> enemiesCount(2,4);
    for(int i=1;i<25;i++)
    {
        int howMany = enemiesCount(generator);
        std::vector<int> X;
        std::vector<int> Y;
        if(Map::stages[i/5][i%5]!= nullptr)
            for(int n=0;n<howMany;n++) {
                int num = enemies(generator);//rand()%4;
                int x;
                int y;
                do {
                    x = rand() % 8;
                    y = rand() % 8;
                } while (Map::stages[i/5][i%5]->obstacles[y][x] != 0 || (std::ranges::find(X.begin(),X.end(),x)!=X.end() && std::ranges::find(Y.begin(),Y.end(),y)!=Y.end()));
                X.push_back(x);
                Y.push_back(y);

                switch (num) {
                    case 0:
                        mapa[i].push_back(std::make_unique<FlyingEnemy>(x * 80 + 105, y * 80 + 90));
                        break;
                    case 1:
                        mapa[i].push_back(std::make_unique<Turret>(x * 80 + 105, y * 80 + 90));
                        break;
                    case 2:
                        mapa[i].push_back(std::make_unique<HumanEnemy>(x * 80 + 105, y * 80 + 90));
                        break;
                    case 3:
                        mapa[i].push_back(std::make_unique<RobotEnemy>(x * 80 + 105, y * 80 + 90));//new RobotEnemy(x*80+105,y*80+90));
                        break;

                }
            }
    }
}

void EnemyVector::updateFlying(sf::RenderWindow& window)
{
    for(auto& e : mapa[Map::getId()])
        if((dynamic_cast<FlyingEnemy*>(e.get())))e->update(window);
    check();
}

void EnemyVector::updateWalking(sf::RenderWindow& window)
{
    for(auto& e : mapa[Map::getId()])
        if(!(dynamic_cast<FlyingEnemy*>(e.get())))e->update(window);
    check();
}

void EnemyVector::check() {
    for(auto it = mapa[Map::getId()].begin(); it<mapa[Map::getId()].end();it++)
        if((*it)->getIsDead())
            mapa[Map::getId()].erase(it);
    if(mapa[Map::getId()].empty()&&!Map::getCurrentStage().getIsCleared()) {
        Map::getCurrentStage().clear();
        Player::stageCleared();
    }
}

void EnemyVector::draw(sf::RenderWindow& window){
    for(auto& e : mapa[Map::getId()])
        e->draw(window);
}

void EnemyVector::buyReduceEnemySpeed(double reduce)
{
    for(auto& e : mapa[Map::getId()])
        e->buyReduceEnemySpeed(reduce);
}

void EnemyVector::resetStatics()
{
    mapa.clear();
}
