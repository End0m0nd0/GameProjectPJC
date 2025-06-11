//
// Created by JEDREK on 24.05.2024.
//

#ifndef UNTITLED_COLLECTABLEVECTOR_H
#define UNTITLED_COLLECTABLEVECTOR_H

#include "CollectItem.h"
#include "Map.h"
#include "SFML/Graphics.hpp"

class CollectableVector {
    static inline std::map<int,std::vector<CollectItem>> mapa;

public:
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    static void add(double x,double y,bool canBeCollected = false);
    static void resetStatics();

};


#endif //UNTITLED_COLLECTABLEVECTOR_H
