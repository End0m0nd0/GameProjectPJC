//
// Created by JEDREK on 21.04.2024.
//

#include "Obstacle.h"
Obstacle::Obstacle(int id, double x, double y) {
    int num; // zeby switch dzialal
    this->x=x;
    this->y=y;
    this->id=id;
    switch (id) {
        case 1:
            for(int i=0;i<4;i++)
                texture.emplace_back();
            texture[0].loadFromFile("Sprites/Obstacles/1/ComputerOne.png");
            texture[1].loadFromFile("Sprites/Obstacles/1/ComputerTwo.png");
            texture[2].loadFromFile("Sprites/Obstacles/1/ComputerThree.png");
            texture[3].loadFromFile("Sprites/Obstacles/1/ComputerFour.png");
            obstacleSprite.setTextureRect(sf::IntRect (0,0,80,80));
            break;
        case 2:
            x+=10;
            y-=50;
            for(int i=0;i<4;i++)
                texture.emplace_back();
            texture[0].loadFromFile("Sprites/Obstacles/2/ReactorOne.png");
            texture[1].loadFromFile("Sprites/Obstacles/2/ReactorTwo.png");
            texture[2].loadFromFile("Sprites/Obstacles/2/ReactorThree.png");
            texture[3].loadFromFile("Sprites/Obstacles/2/ReactorFour.png");
            obstacleSprite.setTextureRect(sf::IntRect (0,0,63,126));
            break;
        case 3:
            for(int i=0;i<20;i++)
                texture.emplace_back();
            texture[0].loadFromFile("Sprites/Obstacles/3/AcidOne.png");
            texture[1].loadFromFile("Sprites/Obstacles/3/AcidTwo.png");
            texture[2].loadFromFile("Sprites/Obstacles/3/AcidThree.png");
            texture[3].loadFromFile("Sprites/Obstacles/3/AcidFour.png");
            texture[4].loadFromFile("Sprites/Obstacles/3/AcidFive.png");
            texture[5].loadFromFile("Sprites/Obstacles/3/AcidSix.png");
            texture[6].loadFromFile("Sprites/Obstacles/3/AcidSeven.png");
            texture[7].loadFromFile("Sprites/Obstacles/3/AcidEight.png");
            texture[8].loadFromFile("Sprites/Obstacles/3/AcidNine.png");
            texture[9].loadFromFile("Sprites/Obstacles/3/AcidTen.png");
            texture[10].loadFromFile("Sprites/Obstacles/3/AcidEleven.png");
            texture[11].loadFromFile("Sprites/Obstacles/3/AcidTwelve.png");
            texture[12].loadFromFile("Sprites/Obstacles/3/AcidThirteen.png");
            texture[13].loadFromFile("Sprites/Obstacles/3/AcidFourteen.png");
            texture[14].loadFromFile("Sprites/Obstacles/3/AcidFifteen.png");
            texture[15].loadFromFile("Sprites/Obstacles/3/AcidSixteen.png");
            texture[16].loadFromFile("Sprites/Obstacles/3/AcidSeventeen.png");
            texture[17].loadFromFile("Sprites/Obstacles/3/AcidEighteen.png");
            texture[18].loadFromFile("Sprites/Obstacles/3/AcidNineteen.png");
            texture[19].loadFromFile("Sprites/Obstacles/3/AcidTwenty.png");
            obstacleSprite.setTextureRect(sf::IntRect (0,0,80,80));
            break;
        case 4:
            texture.emplace_back();
            num = rand()%12;
            switch (num) {
                case 0:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestOneTwo.png"); break;
                case 1:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestOneThree.png");break;
                case 2:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestOneFour.png");break;
                case 3:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestTwoOne.png");break;
                case 4:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestTwoThree.png");break;
                case 5:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestTwoFour.png");break;
                case 6:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestThreeOne.png");break;
                case 7:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestThreeTwo.png");break;
                case 8:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestThreeFour.png");break;
                case 9:  texture[0].loadFromFile("Sprites/Obstacles/4/ChestFourOne.png");break;
                case 10: texture[0].loadFromFile("Sprites/Obstacles/4/ChestFourTwo.png");break;
                case 11: texture[0].loadFromFile("Sprites/Obstacles/4/ChestFourThree.png");break;
            }
            break;
        case 5:
            x+=10;
            y-=50;
            for(int i=0;i<4;i++)
                texture.emplace_back();
            texture[0].loadFromFile("Sprites/Obstacles/5/EmptyReactorOne.png");
            texture[1].loadFromFile("Sprites/Obstacles/5/EmptyReactorTwo.png");
            texture[2].loadFromFile("Sprites/Obstacles/5/EmptyReactorThree.png");
            texture[3].loadFromFile("Sprites/Obstacles/5/EmptyReactorFour.png");
            obstacleSprite.setTextureRect(sf::IntRect (0,0,63,126));
            break;
        case 6:
            texture.emplace_back();
            texture.emplace_back();
            texture[0].loadFromFile("Sprites/Obstacles/6/ChestClosed.png");
            texture[1].loadFromFile("Sprites/Obstacles/6/ChestOpened.png");
            isChest=true;
            break;
        default:
            texture.emplace_back();
            texture[0].loadFromFile("Sprites/Obstacles/1/ComputerOne.png");
            obstacleSprite.setTextureRect(sf::IntRect (0,0,80,80));
            break;

    }

    obstacleSprite.setPosition(x,y);
    obstacleSprite.setTexture(texture[0]);
}

void Obstacle::update() {
    if(!isChest) {
        timer++;
        if (timer % 20 == 0) obstacleSprite.setTexture(texture[currentTexture++]);
        if (currentTexture == texture.size()) currentTexture = 0;
    }
}
bool Obstacle::open(sf::Sprite& playerSprite){
    if(isChest&&!opened) {
        this->playerSprite = playerSprite;
        int centralX = obstacleSprite.getPosition().x + obstacleSprite.getGlobalBounds().width / 2;
        int centralY = obstacleSprite.getPosition().y + obstacleSprite.getGlobalBounds().height / 2;
        int centralEnemyX = playerSprite.getPosition().x;
        if (playerSprite.getScale().x > 0) centralEnemyX += playerSprite.getGlobalBounds().width / 2;
        else centralEnemyX -= playerSprite.getGlobalBounds().width / 2;
        int centralEnemyY = playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2;
        if (abs(centralX - centralEnemyX) < 90 && abs(centralY - centralEnemyY) < 90) {
            currentTexture = 1;
            obstacleSprite.setTexture(texture[currentTexture]);
            opened= true;
            return true;
        }
    }
    return false;
}

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(obstacleSprite);
}

double Obstacle::getX() const
{
    return x;
}
double Obstacle::getY() const
{
    return y;
}