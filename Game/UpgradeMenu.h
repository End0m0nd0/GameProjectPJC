//
// Created by JEDREK on 27.05.2024.
//

#ifndef UNTITLED_UPGRADEMENU_H
#define UNTITLED_UPGRADEMENU_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EnemyVector.h"
#include "CollectableVector.h"
#include "HealthBar.h"
#include "EnemyProjectile.h"
#include "Map.h"

class UpgradeMenu {
    bool isActive = true;
    sf::Font font;
    sf::RectangleShape transparentRectangle;

    bool classChose= true;
    std::vector<sf::RectangleShape> classButtons;
    std::vector<sf::Text> classNamesTexts;
    std::vector<sf::Text> classInfo;
    std::vector<sf::Texture> classTextures;
    std::vector<sf::Sprite> classSprites;
    std::vector<sf::RectangleShape> classIconBorders;
    sf::RectangleShape transparentClassRectangle;

    bool minimap=false;
    sf::RectangleShape stages[5][5];

    bool upgrades= false;
    std::vector<sf::Text> upgradesText;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonsText;
    static int const upNumber=6;
    int price[upNumber];
    int level[upNumber];

public:
    UpgradeMenu();
    void update(sf::RenderWindow& window, Player& player, EnemyVector& enemyVector, Map& map, CollectableVector& collectableVector, HealthBar& healthBar);
    void buy(int i,std::string string);
    void changeToMax(int i);
    bool getIsActive();
    void changeIsActive();
    void openMinimap();
    void openUpgrades();

};


#endif //UNTITLED_UPGRADEMENU_H
