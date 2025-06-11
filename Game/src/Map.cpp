//
// Created by JEDREK on 22.04.2024.
//

#include "Map.h"
#include "Path.h"

Map::Map (){
    leftRightWallsTexture.loadFromFile(Path::get()+"Sprites/Walls/LeftRight.png");
    leftRightWalls.setTexture(leftRightWallsTexture);
    topBottomWallsTexture.loadFromFile(Path::get()+"Sprites/Walls/TopBottom.png");
    topBottomWalls.setTexture(topBottomWallsTexture);
    findPattern();
    patternToStages();
}
void Map::createNew()
{
    currentXstage=0;
    currentYstage=0;
    stages.clear();
    findPattern();
    patternToStages();
}


void Map::findPattern()
{
    do {
        int amount=0;
        for (int i = 0; i < size; i++)
            for (int n = 0; n < size; n++) {
                if (rand() % 2 == 0)
                    pattern[i][n] = false;
                else pattern[i][n] = true;

            }
        pattern[0][0]= true;
        pattern[4][4]= true;
    } while (!hasPath());
}
void Map::patternToStages()
{
    for(int i=0;i<size;i++){
        stages.push_back(std::vector<std::unique_ptr<Stage>>());
        for (int n = 0; n < size; n++)
            if(i==0&&n==0) stages[i].push_back(std::make_unique<Stage>(true));
            else if (pattern[i][n]) stages[i].push_back(std::make_unique<Stage>());
            else stages[i].push_back(nullptr);
    }
}

void Map::drawWalls(sf::RenderWindow& window)
{

    topBottomWalls.setTexture(topBottomWallsTexture);
    leftRightWalls.setTexture(leftRightWallsTexture);

    topBottomWalls.setPosition(0,0);
    leftRightWalls.setPosition(0,0);
    for(int i=0;i<10;i++) {
        if(i==4)i=6;
        topBottomWalls.setPosition(i*80,0);
        window.draw(topBottomWalls);
    }
    leftRightWalls.setScale(1,1);
    leftRightWalls.setPosition(0,0);
    window.draw(leftRightWalls);
    leftRightWalls.setPosition(0,480);
    window.draw(leftRightWalls);

    for(int i=0;i<10;i++) {
        if(i==4)i=6;
        topBottomWalls.setPosition(i*80,720);
        window.draw(topBottomWalls);
    }

    leftRightWalls.setScale(-1,1);
    leftRightWalls.setPosition(800,0);
    window.draw(leftRightWalls);
    leftRightWalls.setPosition(800,480);
    window.draw(leftRightWalls);


    if(currentYstage==0)  //GĂłra
    {
        topBottomWalls.setPosition(320,0);
        window.draw(topBottomWalls);
        topBottomWalls.setPosition(400,0);
        window.draw(topBottomWalls);
        top=false;
    }
    else if(!pattern[currentYstage-1][currentXstage])
    {
        topBottomWalls.setPosition(320,0);
        window.draw(topBottomWalls);
        topBottomWalls.setPosition(400,0);
        window.draw(topBottomWalls);
        top=false;
    }
    else top=true;

    if(currentYstage==size-1)    //DĂłĹ‚
    {
        topBottomWalls.setPosition(320,720);
        window.draw(topBottomWalls);
        topBottomWalls.setPosition(400,720);
        window.draw(topBottomWalls);
        bottom= false;
    }
    else if(!pattern[currentYstage+1][currentXstage])
    {
        topBottomWalls.setPosition(320,720);
        window.draw(topBottomWalls);
        topBottomWalls.setPosition(400,720);
        window.draw(topBottomWalls);
        bottom= false;
    }
    else bottom= true;

    if(currentXstage==0) // lewo
    {
        leftRightWalls.setScale(1,1);
        leftRightWalls.setPosition(0,240);
        window.draw(leftRightWalls);
        left=false;
    }
    else if(!pattern[currentYstage][currentXstage-1])
    {
        leftRightWalls.setScale(1,1);
        leftRightWalls.setPosition(0,240);
        window.draw(leftRightWalls);
        left=false;
    }
    else left= true;

    if(currentXstage==size-1)  //prawo
    {
        leftRightWalls.setScale(-1,1);
        leftRightWalls.setPosition(800,240);
        window.draw(leftRightWalls);
        right=false;
    }
    else if(!pattern[currentYstage][currentXstage+1])
    {
        leftRightWalls.setScale(-1,1);
        leftRightWalls.setPosition(800,240);
        window.draw(leftRightWalls);
        right=false;
    }
    else right=true;

    window.draw(classText);
}

bool Map::getLeft()
{
    return left;
}
bool Map::getTop()
{
    return top;
}
bool Map::getRight()
{
    return right;
}
bool Map::getBottom()
{
    return bottom;
}
void Map::xAdd()
{
    currentXstage++;
}
void Map::xSub()
{
    currentXstage--;
}
void Map::yAdd()
{
    currentYstage++;
}
void Map::ySub()
{
    currentYstage--;
}
int Map::getId()
{
    return currentYstage*size+currentXstage;
}
Stage& Map::getCurrentStage()
{
    return *stages[currentYstage][currentXstage];
}

void Map::resetStatics()
{
    currentXstage=0;
    currentYstage=0;
}

void Map::setClassText(sf::Text text)
{
    classText = text;
    classText.setPosition(30,750);
    classText.setOutlineColor(sf::Color::Black);
    classText.setOutlineThickness(3);
}

bool Map::didWin() {
    for(int i=0;i<5;i++)
        for(int n=0;n<5;n++)
            if(stages[i][n]!= nullptr)
                if(!stages[i][n]->getIsCleared())
                    return false;
    return true;
}

bool Map::hasPath() {
    int check [5][5];
    for(int i=0;i<5;i++)
        for(int n=0;n<5;n++)
            if(pattern[i][n]) check[i][n]=1;
            else check[i][n]=0;

            check[0][0]=2;
    for(int i=0;i<17;i++){
        for(int z=0;z<5;z++) {
            for (int t = 0; t < 5; t++) {

                if (z != 0 && z != 4 && t != 0 && t != 4) {
                    if (check[z][t] == 2) {
                        if (check[z + 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z - 1][t] == 1) check[z - 1][t] = 2;
                        if (check[z][t + 1] == 1) check[z][t + 1] = 2;
                        if (check[z][t - 1] == 1) check[z][t - 1] = 2;
                    }
                } else if (z > 0 && z < 4 && t == 0) {
                    if (check[z][t] == 2) {
                        if (check[z + 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z - 1][t] == 1) check[z - 1][t] = 2;
                        if (check[z][t + 1] == 1) check[z][t + 1] = 2;
                    }
                } else if (z > 0 && z < 4 && t == 4) {
                    if (check[z][t] == 2) {
                        if (check[z + 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z - 1][t] == 1) check[z - 1][t] = 2;
                        if (check[z][t - 1] == 1) check[z][t - 1] = 2;
                    }
                } else if (t > 0 && t < 4 && z == 0) {
                    if (check[z][t] == 2) {
                        if (check[z + 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z][t + 1] == 1) check[z][t + 1] = 2;
                        if (check[z][t - 1] == 1) check[z][t - 1] = 2;
                    }
                } else if (t > 0 && t < 4 && z == 4) {
                    if (check[z][t] == 2) {
                        if (check[z - 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z][t + 1] == 1) check[z][t + 1] = 2;
                        if (check[z][t - 1] == 1) check[z][t - 1] = 2;
                    }
                } else if (z == 0 && t == 0) {
                    if (check[z][t] == 2) {
                        if (check[z + 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z][t + 1] == 1) check[z][t + 1] = 2;
                    }
                } else if (z == 0 && t == 4) {
                    if (check[z][t] == 2) {
                        if (check[z + 1][t] == 1) check[z + 1][t] = 2;
                        if (check[z][t - 1] == 1) check[z][t - 1] = 2;
                    }
                } else if (z == 4 && t == 0) {
                    if (check[z][t] == 2) {
                        if (check[z - 1][t] == 1) check[z - 1][t] = 2;
                        if (check[z][t + 1] == 1) check[z][t + 1] = 2;
                    }
                } else if (z == 4 && t == 4) {
                    if (check[z][t] == 2) {
                        if (check[z - 1][t] == 1) check[z - 1][t] = 2;
                        if (check[z][t - 1] == 1) check[z][t - 1] = 2;
                    }
                }
            }
        }
    }
    int amount =0;
    for (int i = 0; i < size; i++)
        for (int n = 0; n < size; n++)
            if(pattern[i][n]) amount++;
    if(amount<16||amount>18)
        return false;

    for(int i=0;i<5;i++)
        for(int n=0;n<5;n++)
            if(check[i][n]==1) return false;
    return true;
}
