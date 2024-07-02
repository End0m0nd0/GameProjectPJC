//
// Created by JEDREK on 07.05.2024.
//

#include "Directions.h"
bool Directions::canMoveLeft(sf::Sprite& sprite) // currentXTile - współrzędna X lewej strony sprite'a CurrentRightXtile - analogicznie prawa strona
{
    if(sprite.getScale().x>0) return true;

    double width = sprite.getGlobalBounds().width;
    double height = sprite.getGlobalBounds().height;
    double x=sprite.getPosition().x;
    double y=sprite.getPosition().y;
    Stage &stage = Map::getCurrentStage();

    int currentXtile,currentRightXtile,currentYtile,currentDownYtile;
    currentXtile = (int) ((x - 80 - width) / 80);
    currentRightXtile = (int) (x - 80) / 80;
    currentYtile = (int) ((y - 80 + 5) / 80);
    currentDownYtile = (int) (y - 80 + height-5) / 80;
    if(x-width<80||y+height>720||x<80) return true;
    if(sprite.getScale().x<0)
        if((stage.obstacles[currentYtile][currentXtile]!=0&&stage.obstacles[currentYtile][currentRightXtile-1]!=0)||
           stage.obstacles[currentDownYtile][currentXtile]!=0&&stage.obstacles[currentDownYtile][currentRightXtile-1]!=0)
            return false;
    return true;
}
bool Directions::canMoveRight(sf::Sprite& sprite)
{
    if(sprite.getScale().x<0) return true;

    double width = sprite.getGlobalBounds().width;
    double height = sprite.getGlobalBounds().height;
    double x=sprite.getPosition().x;
    double y=sprite.getPosition().y;
    Stage &stage = Map::getCurrentStage();


    int currentXtile,currentRightXtile,currentYtile,currentDownYtile;
    currentXtile = (int) ((x - 80) / 80);
    currentRightXtile = (int) (x - 80 + width) / 80;
    currentYtile = (int) ((y - 80 + 5) / 80);
    currentDownYtile = (int) (y - 80 + height-5) / 80;
    if(x+width>720||y+height>720) return true;
    if(sprite.getScale().x>0)
        if((stage.obstacles[currentYtile][currentRightXtile]!=0&&stage.obstacles[currentYtile][currentXtile+1]!=0)||
           stage.obstacles[currentDownYtile][currentRightXtile]!=0&&stage.obstacles[currentDownYtile][currentXtile+1]!=0)
            return false;
    return true;
}

bool Directions::canMoveDown(sf::Sprite& sprite)
{
    double width = sprite.getGlobalBounds().width;
    double height = sprite.getGlobalBounds().height;
    double x=sprite.getPosition().x;
    double y=sprite.getPosition().y;
    Stage &stage = Map::getCurrentStage();

    int currentXtile,currentRightXtile,currentYtile,currentDownYtile;

    if(sprite.getScale().x>0) {
        currentXtile = (int) ((x - 80 + 5) / 80);
        currentRightXtile = (int) (x - 80 + width - 5) / 80;
    }
    else{
        currentXtile = (int) ((x - 80 - width+5) / 80);
        currentRightXtile = (int) (x - 80-5) / 80;
    }
    currentYtile = (int) ((y - 80) / 80);
    currentDownYtile = (int) (y - 80 + height) / 80;
    if(y+height>720) return true;
    if((stage.obstacles[currentDownYtile][currentXtile]!=0&&stage.obstacles[currentYtile+1][currentXtile]!=0)||
       stage.obstacles[currentDownYtile][currentRightXtile]!=0&&stage.obstacles[currentYtile+1][currentRightXtile]!=0)
        return false;
    return true;
}

bool Directions::canMoveUp(sf::Sprite& sprite)
{
    double width = sprite.getGlobalBounds().width;
    double height = sprite.getGlobalBounds().height;
    double x=sprite.getPosition().x;
    double y=sprite.getPosition().y;
    Stage &stage = Map::getCurrentStage();

    int currentXtile,currentRightXtile,currentYtile,currentDownYtile;

    if(sprite.getScale().x>0) {
        currentXtile = (int) ((x - 80 + 5) / 80);
        currentRightXtile = (int) (x - 80 + width - 5) / 80;
    }
    else{
        currentXtile = (int) ((x - 80 - width+5) / 80);
        currentRightXtile = (int) (x - 80-5) / 80;
    }
    currentYtile = (int) ((y - 80) / 80);
    currentDownYtile = (int) (y - 80 + height) / 80;
    if(y+height>720) return true;
    if(((sprite.getScale().x>0&&x>320&&x<480)||(sprite.getScale().x<0&&x-width>320&&x-width<480))&&Map::getTop()&&y+height<160) return true;
    if(y<80) return false;
    if((stage.obstacles[currentYtile][currentXtile]!=0&&stage.obstacles[currentDownYtile-1][currentXtile]!=0)||
       stage.obstacles[currentYtile][currentRightXtile]!=0&&stage.obstacles[currentDownYtile-1][currentRightXtile]!=0)
        return false;
    return true;
}