//
// Created by JEDREK on 24.05.2024.
//

#include "CollectItem.h"
#include "Path.h"

CollectItem::CollectItem(double x, double y,bool canBeCollected) : x(x), y(y), startY(y), canBeCollected(canBeCollected){
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> item(1, 4);
    id = item(generator);
    switch(id){
        case 1:
            texture.loadFromFile(Path::get()+"Sprites/UI/EmptyHealth.png");
            break;
        case 2:
            texture.loadFromFile(Path::get()+"Sprites/UI/FullHealth.png");
            break;
        case 3:
            texture.loadFromFile(Path::get()+"Sprites/UI/Coin.png");
            break;
        case 4:
            texture.loadFromFile(Path::get()+"Sprites/UI/DoubleCoin.png");
            break;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
}


void CollectItem::update(sf::RenderWindow& window){
    if(!isCollected){
        if(!canBeCollected)
        {
            y-=0.5;
            if(startY-y>80) canBeCollected= true;
        }
        else
        {
            if(sprite.getGlobalBounds().intersects(Player::player().getGlobalBounds()))
            {
                isCollected= true;
                switch (id) {
                    case 1:
                        Player::collectMaxHealth();
                        break;
                    case 2:
                        Player::collectHealth();
                        break;
                    case 3:
                        Player::collectCoin();
                        break;
                    case 4:
                        Player::collectDoubleCoin();
                        break;
                }
            }
        }
        sprite.setPosition(x,y);
        sprite.setTexture(texture);
        window.draw(sprite);
    }
}

void CollectItem::draw(sf::RenderWindow& window){
    if(!isCollected)
        window.draw(sprite);
}
