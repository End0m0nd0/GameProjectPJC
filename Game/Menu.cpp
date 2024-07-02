//
// Created by JEDREK on 29.05.2024.
//

#include "Menu.h"
Menu::Menu()
        : transparentRectangle(), playButton(), controlsButton(), backFromControlsPanelButton(),
          backFromGameOverPanelButton(), playAgainButton(), transparentRectangleFull() {
    ////////////Do Main Menu ///////////
    transparentRectangle = sf::RectangleShape(sf::Vector2f(560, 800));
    transparentRectangle.setFillColor(sf::Color(0,0,0,220));

    playButton = sf::RectangleShape(sf::Vector2f(242, 72));
    playButton.setPosition(155,240);
    playButton.setFillColor(sf::Color(60,80,100,200));
    playButton.setOutlineThickness(2);
    playButton.setOutlineColor(sf::Color(160,160,160));

    controlsButton = playButton;
    controlsButton.setPosition(155,480);

    font.loadFromFile("Fonts/fontOne.otf");

    playText = sf::Text("Play",font,35);
    playText.setFillColor(sf::Color(220,215,215));
    playText.setPosition(225,250);

    controlsText = sf::Text("Controls",font,35);
    controlsText.setFillColor(sf::Color(220,215,215));
    controlsText.setPosition(190,490);

    playerTexture.loadFromFile("Sprites/PlayerSprites/PlayerSprite.png");
    player.setScale(-4,4);
    player.setPosition(700,300);
    player.setTexture(playerTexture);
    ////////////Do Main Menu ///////////

    ////////////Do Controls Panel ///////////
    transparentRectangleFull = sf::RectangleShape(sf::Vector2f(800, 800));
    transparentRectangleFull.setFillColor(sf::Color(0,0,0,220));
    for(int i=0;i<5;i++)
    {
        std::string strLeft;
        std::string strRight;
        switch(i){
            case 0:
                strLeft ="WSAD";
                strRight = "Move";
                break;
            case 1:
                strLeft ="Mouse Button";
                strRight = "Shoot";
                break;
            case 2:
                strLeft ="M";
                strRight = "Open Minimap";
                break;
            case 3:
                strLeft ="Space";
                strRight = "Open Chest";
                break;
            case 4:
                strLeft ="Tab";
                strRight = "Open Upgrades Menu";
                break;
            default:
                strLeft ="EMPTY";
                strRight = "EMPTY";
                break;
        }
        controlsInfoTextsLeft.emplace_back(strLeft,font,30);
        controlsInfoTextsLeft[i].setPosition(40,40+i*120);
        controlsInfoTextsRight.emplace_back(strRight,font,controlsInfoTextsLeft[i].getCharacterSize());
        controlsInfoTextsRight[i].setPosition(760-controlsInfoTextsRight[i].getGlobalBounds().width,controlsInfoTextsLeft[i].getPosition().y);

        backFromControlsPanelButton = sf::RectangleShape(sf::Vector2f(160, 60));
        backFromControlsPanelButton.setPosition(320,650);
        backFromControlsPanelButton.setFillColor(sf::Color(60,80,100,200));
        backFromControlsPanelButton.setOutlineThickness(2);
        backFromControlsPanelButton.setOutlineColor(sf::Color(160,160,160));

        backFromControlsPanelText = sf::Text("Back",font,35);
        backFromControlsPanelText.setFillColor(sf::Color(220,215,215));
        backFromControlsPanelText.setPosition(345,655);
    }
    ////////////Do Controls Panel ///////////

    ////////////Do Game OverPanel ///////////
    backFromGameOverPanelButton=backFromControlsPanelButton;
    backFromGameOverPanelButton.setPosition(320,570);

    backFromGameOverPanelText = backFromControlsPanelText;
    backFromGameOverPanelText.setPosition(345,575);

    playAgainButton = backFromControlsPanelButton;
    playAgainButton.setSize(sf::Vector2f (320,60));
    playAgainButton.setPosition(240,335);

    playAgainText = backFromControlsPanelText;
    playAgainText.setString("Play Again");
    playAgainText.setPosition(280,340);

    pointsText.setPosition(200,140);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setOutlineColor(sf::Color::Black);
    pointsText.setOutlineThickness(4);
    pointsText.setFont(font);
    ////////////Do Game OverPanel ///////////

}

void Menu::update(sf::RenderWindow& window) {

    stage.drawBg(window);
    stage.updateOb(window);

    if(isMainMenuActive) {

        window.draw(transparentRectangle);
        window.draw(playButton);
        window.draw(playText);
        window.draw(controlsButton);
        window.draw(controlsText);
    }else if(isControlPanelActive){
        window.draw(transparentRectangleFull);
        for(auto& text : controlsInfoTextsLeft)
            window.draw(text);

        for(auto& text : controlsInfoTextsRight)
            window.draw(text);
        window.draw(backFromControlsPanelButton);
        window.draw(backFromControlsPanelText);
    }else if(isGameOverPanelActive){

        window.draw(transparentRectangleFull);
        window.draw(backFromGameOverPanelButton);
        window.draw(backFromGameOverPanelText);
        window.draw(playAgainButton);
        window.draw(playAgainText);
        window.draw(pointsText);
    }

    auto event = sf::Event();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if(event.type==sf::Event::MouseButtonPressed) {
            auto mousePos = sf::Mouse::getPosition(window);
            if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)&&isMainMenuActive)
                changeIsActive();
            else if (controlsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)&&isMainMenuActive) {
                isMainMenuActive=false;
                isControlPanelActive= true;
            }
            else if(backFromControlsPanelButton.getGlobalBounds().contains(mousePos.x,mousePos.y)&&isControlPanelActive)
            {
                isMainMenuActive= true;
                isControlPanelActive=false;
            }
            else if(backFromGameOverPanelButton.getGlobalBounds().contains(mousePos.x, mousePos.y)&&isGameOverPanelActive)
            {
                isMainMenuActive= true;
                isGameOverPanelActive = false;
            }
            else if(playAgainButton.getGlobalBounds().contains(mousePos.x,mousePos.y)&&isGameOverPanelActive){
                isActive=false;
            }
        }
    }
}

void Menu::changeIsActive()
{
    isActive=!isActive;
}
bool Menu::getIsActive() const
{
    return isActive;
}

void Menu::lost(int points)
{
    pointsText.setString("You cleared: "+std::to_string(points)+" Stages" );
    if(points==100)
        pointsText.setString("You win" );
    pointsText.setPosition((800-pointsText.getGlobalBounds().width)/2,140);
    isActive= true;
    isMainMenuActive=false;
    isGameOverPanelActive= true;
}