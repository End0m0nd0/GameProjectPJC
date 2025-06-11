//
// Created by JEDREK on 27.05.2024.
//

#include "UpgradeMenu.h"
#include "Path.h"

UpgradeMenu::UpgradeMenu() : transparentRectangle(), transparentClassRectangle() {
    font.loadFromFile(Path::get()+"Fonts/fontOne.otf");
    Map::setClassText(sf::Text());
    for(int i=0;i<4;i++){
        int x;
        int y;
        classNamesTexts.push_back(sf::Text());
        classInfo.push_back(sf::Text());
        classSprites.push_back(sf::Sprite());
        classTextures.push_back(sf::Texture());
        classIconBorders.push_back(sf::RectangleShape());
        switch (i) {
            case 0:
                classTextures[i].loadFromFile(Path::get()+"Sprites/PlayerSprites/ClassIcons/BerserkOne.png");
                classNamesTexts[i].setString("Berserk");
                classInfo[i].setString("No hearts limits");
                x=80;
                y=80;
                break;
            case 1:
                classTextures[i].loadFromFile(Path::get()+"Sprites/PlayerSprites/ClassIcons/SprinterOne.png");
                classNamesTexts[i].setString("Sprinter");
                classInfo[i].setString("1.5x speed");
                x=480;
                y=80;
                break;
            case 2:
                classTextures[i].loadFromFile(Path::get()+"Sprites/PlayerSprites/ClassIcons/DevastatorOne.png");
                classNamesTexts[i].setString("Devastator");
                classInfo[i].setString("2x Damage");
                x=80;
                y=480;
                break;
            case 3:
                classTextures[i].loadFromFile(Path::get()+"Sprites/PlayerSprites/ClassIcons/LuckyMan.png");
                classNamesTexts[i].setString("Lucky Man");
                classInfo[i].setString("100% loot \nfrom enemies\n+10 coins");
                x=480;
                y=480;
                break;
        }
        classSprites[i].setTexture(classTextures[i]);
        classButtons.push_back(sf::RectangleShape());
        classButtons[i].setFillColor(sf::Color(0,0,0,220));
        classButtons[i].setSize(sf::Vector2f(240,240));
        classButtons[i].setPosition(x,y);

        classNamesTexts[i].setFont(font);
        classNamesTexts[i].setPosition(x+10,y+10);
        classInfo[i].setFont(font);
        classInfo[i].setCharacterSize(17);
        classInfo[i].setPosition(classNamesTexts[i].getPosition().x,classNamesTexts[i].getPosition().y+60);
        classSprites[i].setPosition(x+140,y+140);
        classSprites[i].setScale(2.2,2.2);
        classIconBorders[i].setSize(sf::Vector2f (classSprites[i].getGlobalBounds().width+4,classSprites[i].getGlobalBounds().height+4));
        classIconBorders[i].setPosition(classSprites[i].getPosition().x-2,classSprites[i].getPosition().y-2);

    }
    transparentClassRectangle.setSize(sf::Vector2f (800,800));
    transparentClassRectangle.setFillColor(sf::Color(0,0,0,160));

    for(int i=0;i<5;i++)
        for(int n=0;n<5;n++){
            stages[i][n].setSize(sf::Vector2f (100,60));
            stages[i][n].setPosition(i*150+50,n*120+150);
            stages[i][n].setFillColor(sf::Color::Yellow);
            stages[i][n].setOutlineThickness(1.5);
            stages[i][n].setOutlineColor(sf::Color::White);
        }

    for(int i=0;i<upNumber;i++){
        price[i]=1;
        level[i]=1;

        std::string str ;
        switch (i) {
            case 0:
                str = "Reduce reload time                  level 1";
                break;
            case 1:
                str = "Increase speed                        level 1";
                break;
            case 2:
                str = "Reduce enemy speed              level 1";
                break;
            case 3:
                str = "Reduce enemy bullet speed     level 1";
                break;
            case 4:
                price[4]=2;
                str = "Increase max health";
                break;
            case 5:
                price[5]=2;
                str = "Heal";
                break;
            default:
                str="EMPTY";
        }
        upgradesText.push_back(sf::Text(str,font,22));
        upgradesText[i].setPosition(90,i*80+180);
        buttons.push_back(sf::RectangleShape(sf::Vector2f(70, 30)));
        buttons[i].setPosition(675,i*80+180);
        buttons[i].setOutlineThickness(3);
        buttons[i].setOutlineColor(sf::Color(0,0,0));
        buttons[i].setFillColor(sf::Color(200,200,200));

        buttonsText.push_back(sf::Text("1",font,24));
        buttonsText[i].setPosition(buttons[i].getPosition().x+buttons[i].getGlobalBounds().width/5,buttons[i].getPosition().y);
        buttonsText[i].setFillColor(sf::Color(0,0,0));

        if(i==5||i==4) buttonsText[i].setString("2");
    }

    transparentRectangle = sf::RectangleShape(sf::Vector2f(800, 800));
    transparentRectangle.setFillColor(sf::Color(0,0,0,220));
}
void UpgradeMenu::update(sf::RenderWindow& window, Player& player, EnemyVector& enemyVector, Map& map, CollectableVector& collectableVector, HealthBar& healthBar){
    map.getCurrentStage().drawBg(window);
    player.draw(window);
    enemyVector.draw(window);
    map.getCurrentStage().drawOb(window);
    map.drawWalls(window);
    collectableVector.draw(window);

    for (Projectile &projectile: Player::getProjectiles())
        projectile.draw(window);
    for (EnemyProjectile &enemyProjectile: Enemy::getEnemyProjectiles())
        enemyProjectile.draw(window);
    if(classChose){
        window.draw(transparentClassRectangle);
        for(int i=0;i<4;i++)
        {
            classNamesTexts[i].setFont(font);
            classInfo[i].setFont(font);
            classSprites[i].setTexture(classTextures[i]);

            window.draw(classButtons[i]);
            window.draw(classNamesTexts[i]);
            window.draw(classInfo[i]);
            window.draw(classIconBorders[i]);
            window.draw(classSprites[i]);
        }

        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = sf::Mouse::getPosition(window); // 1 - berserk, 2-sprinter, 3-devastator, 4- lucky man
                if (classButtons[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    Player::setClass(1);
                    buttonsText[4].setString("0");
                    Map::setClassText(classNamesTexts[0]);
                    classChose=false;
                    isActive=false;
                }
                else if (classButtons[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    Player::setClass(2);
                    Map::setClassText(classNamesTexts[1]);
                    classChose=false;
                    isActive=false;
                }
                if (classButtons[2].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    Player::setClass(3);
                    Map::setClassText(classNamesTexts[2]);
                    classChose=false;
                    isActive=false;
                }
                if (classButtons[3].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    for(int i=0;i<5;i++) Player::collectDoubleCoin();
                    Player::setClass(4);
                    Map::setClassText(classNamesTexts[3]);
                    classChose=false;
                    isActive=false;
                }
            }
        }
    }
    else if(minimap){
        window.draw(transparentRectangle);
        for(int i=0;i<5;i++)
            for(int n=0;n<5;n++) {
                if(Map::getId() % 5 + 1 != 5)
                    if (Map::stages[Map::getId() / 5][Map::getId() % 5+1] != nullptr)
                        stages[Map::getId() % 5 + 1][Map::getId() / 5].setFillColor(sf::Color::Black);

                if(Map::getId() % 5 - 1 != -1)
                    if (Map::stages[Map::getId() / 5][Map::getId() % 5-1] != nullptr)
                        stages[Map::getId() % 5 - 1][Map::getId() / 5].setFillColor(sf::Color::Black);

                if(Map::getId() / 5 + 1 != 5)
                    if (Map::stages[Map::getId() / 5 + 1][Map::getId() % 5] != nullptr)
                        stages[Map::getId() % 5][Map::getId() / 5 + 1].setFillColor(sf::Color::Black);

                if(Map::getId() / 5 - 1 != -1)
                    if (Map::stages[Map::getId() / 5 - 1][Map::getId() % 5] != nullptr)
                        stages[Map::getId() % 5][Map::getId() / 5 - 1].setFillColor(sf::Color::Black);

                if(Map::stages[n][i]!= nullptr)
                if(Map::stages[n][i]->getIsCleared())
                    stages[i][n].setFillColor(sf::Color::Green);
                if(i==Map::getId()%5&&n==Map::getId()/5)
                    stages[i][n].setFillColor(sf::Color::Red);


                if(Map::stages[n][i]!= nullptr && stages[i][n].getFillColor()!=sf::Color::Yellow)
                    window.draw(stages[i][n]);
            }


        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::M) {
                    minimap=false;
                    changeIsActive();
                }
        }

    }


    else if(upgrades)
    {
        window.draw(transparentRectangle);
        healthBar.Update(window);
        for(auto& text : upgradesText) {
            text.setFont(font);
            window.draw(text);
        }
        for(auto& button : buttons)
            window.draw(button);
        for(auto& buttonText : buttonsText) {
            buttonText.setFont(font);
            window.draw(buttonText);
        }


        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Tab) {
                    upgrades= false;
                    changeIsActive();
                }
            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = sf::Mouse::getPosition(window);
                if (buttons[0].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (Player::getCoins() >= price[0]) {
                        if (Player::canBuyReloadTime()) {
                            buy(0, "Reduce reload time                  level ");
                            Player::buyReloadTime();
                        }
                        if (!Player::canBuyReloadTime())
                            changeToMax(0);
                    }
                } else if (buttons[1].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (Player::getCoins() >= price[1]) {
                        if (Player::canBuyIncreaseSpeed()) {
                            buy(1, "Increase speed                        level ");
                            Player::buyIncreaseSpeed();
                        }
                        if (!Player::canBuyIncreaseSpeed())
                            changeToMax(1);
                    }
                } else if (buttons[2].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (Player::getCoins() >= price[2]) {
                        if (level[2] <= 7) {
                            buy(2, "Reduce enemy speed              level ");
                            EnemyVector::buyReduceEnemySpeed(0.94);
                        }
                        if (level[2] == 8)
                            changeToMax(2);
                    }
                } else if (buttons[3].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (Player::getCoins() >= price[3]) {
                        if (EnemyProjectile::canBuyReduceBulletSpeed()) {
                            buy(3, "Reduce enemy bullet speed     level ");
                            EnemyProjectile::buyReduceBulletSpeed();
                        }
                        if (!EnemyProjectile::canBuyReduceBulletSpeed())
                            changeToMax(3);
                    }
                } else if (buttons[4].getGlobalBounds().contains(mousePos.x, mousePos.y )&& Player::getClass()!=1) {
                    if (Player::getCoins() >= price[4]) {
                        Player::buy(price[4]);
                        price[4]++;
                        buttonsText[4].setString(std::to_string(price[4]));
                        Player::collectMaxHealth();
                    }
                } else if (buttons[5].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (Player::getCoins() >= price[5] && Player::canBuyHeal()) {
                        Player::buy(price[5]);
                        Player::collectHealth();
                    }
                }
            }
        }
    }
}

void UpgradeMenu::buy(int i,std::string string){
    Player::buy(price[i]);
    price[i]+=2;
    level[i]++;
    upgradesText[i].setString(
            string + std::to_string(level[i]));
    buttonsText[i].setString(std::to_string(price[i]));
}

void UpgradeMenu::changeToMax(int i)
{
    buttonsText[i].setString("max");
    buttonsText[i].setPosition(buttons[i].getPosition().x+5,buttonsText[i].getPosition().y);
}

bool UpgradeMenu::getIsActive()
{
    return isActive;
}

void UpgradeMenu::changeIsActive()
{
    isActive=!isActive;
}

void UpgradeMenu::openMinimap()
{
    minimap= true;
}

void UpgradeMenu::openUpgrades() {
    upgrades=true;
}

