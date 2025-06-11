//
// Created by JEDREK on 29.05.2024.
//

#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include "Background.h"
#include "Stage.h"

class Menu {
private:
    bool isControlPanelActive=false;
    bool isMainMenuActive= true;
    bool isGameOverPanelActive=false;
    bool isActive= true;

    ////////////Do Main Menu ///////////
    sf::RectangleShape transparentRectangle;
    sf::RectangleShape playButton;
    sf::RectangleShape controlsButton;
    sf::Text playText;
    sf::Text controlsText;
    ////////////Do Main Menu ///////////


    ////////////Do Controls Panel ///////////
    std::vector<sf::Text> controlsInfoTextsLeft;
    std::vector<sf::Text> controlsInfoTextsRight;
    sf::RectangleShape backFromControlsPanelButton;
    sf::Text backFromControlsPanelText;
    ////////////Do Controls Panel ///////////

    ////////////Do Game OverPanel ///////////
    sf::RectangleShape backFromGameOverPanelButton;
    sf::RectangleShape playAgainButton;
    sf::Text backFromGameOverPanelText;
    sf::Text playAgainText;
    sf::Text pointsText;
    ////////////Do Game OverPanel ///////////

    sf::RectangleShape transparentRectangleFull;
    sf::Font font;
    sf::Sprite player;
    sf::Texture playerTexture;
    Background background;
    Stage stage;

public:
    Menu();
    void update(sf::RenderWindow& window);
    void changeIsActive();
    bool getIsActive() const;
    void lost(int points);
};


#endif //UNTITLED_MENU_H
