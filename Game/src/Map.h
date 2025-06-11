//
// Created by JEDREK on 22.04.2024.
//

#ifndef UNTITLED_MAP_H
#define UNTITLED_MAP_H
#include "Stage.h"

class Map {
private:
    static const int size = 5;
    static inline int currentXstage=0;
    static inline int currentYstage=0;
    sf::Sprite topBottomWalls;
    sf::Texture topBottomWallsTexture;
    sf::Sprite leftRightWalls;
    sf::Texture leftRightWallsTexture;
    static inline bool left,top,right,bottom;
    static inline sf::Text classText;
    bool pattern[size][size];

public:
    static inline std::vector<std::vector<std::unique_ptr<Stage>>> stages;
    Map ();
    void createNew();
    void findPattern();
    void patternToStages();
    void drawWalls(sf::RenderWindow& window);
    static bool getLeft();
    static bool getTop();
    static bool getRight();
    static bool getBottom();
    static void xAdd();
    static void xSub();
    static void yAdd();
    static void ySub();
    static int getId();
    static Stage& getCurrentStage();
    static void resetStatics();
    static void setClassText(sf::Text text);
    static bool didWin();
    bool hasPath();

};




#endif //UNTITLED_MAP_H