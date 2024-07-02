//
// Created by JEDREK on 19.04.2024.
//

#include "Background.h"

Background::Background() {
    renderNew();
    }

void Background::renderNew(){
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, 4);
    srand((unsigned)time(0));
    textures[0].loadFromFile("Sprites/PlayerSprites/Floor/FloorOne.png");
    textures[1].loadFromFile("Sprites/PlayerSprites/Floor/FloorTwo.png");
    textures[2].loadFromFile("Sprites/PlayerSprites/Floor/FloorThree.png");
    textures[3].loadFromFile("Sprites/PlayerSprites/Floor/FloorFour.png");
    textures[4].loadFromFile("Sprites/PlayerSprites/Floor/FloorFive.png");
    for(int i=0;i<rows;i++)
        for(int n=0;n<columns;n++)
        {
            int los = rand()%10;
            floorSpritesTextureNumber[i][n]=distribution(generator);
            if(los<4)
                floorSpritesTextureNumber[i][n]=2;

            floorSprites[i][n].setTexture(textures[floorSpritesTextureNumber[i][n]]);
            floorSprites[i][n].setScale(0.8*(100/96),0.8*(100/96)); //100/96 przez wymiary obrazka 96x96
            floorSprites[i][n].setTextureRect(sf::IntRect(0,0,1000,1000));
            floorSprites[i][n].setPosition(n*100*(100/96)*floorSprites[i][n].getScale().x,i*100*(100/96)*floorSprites[i][n].getScale().y);
        }
    }

void Background::draw(sf::RenderWindow& window)
    {
    for(int i=0;i<rows;i++)
        for(int n=0;n<columns;n++)
        {
            floorSprites[i][n].setTexture(textures[floorSpritesTextureNumber[i][n]]);
            window.draw(floorSprites[i][n]);
        }
    }