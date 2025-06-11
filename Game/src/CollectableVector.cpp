//
// Created by JEDREK on 24.05.2024.
//

#include "CollectableVector.h"
void CollectableVector::update(sf::RenderWindow& window)
{
    for(auto& item : mapa[Map::getId()])
        item.update(window);
}

void CollectableVector::draw(sf::RenderWindow& window)
{
    for(auto& item : mapa[Map::getId()])
        item.draw(window);
}

void CollectableVector::add(double x,double y,bool canBeCollected)
{
    mapa[Map::getId()].push_back(CollectItem(x,y,canBeCollected));
}

void CollectableVector::resetStatics()
{
    mapa.clear();
}