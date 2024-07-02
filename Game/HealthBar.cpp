//
// Created by JEDREK on 30.04.2024.
//

#include "HealthBar.h"
HealthBar::HealthBar()
{
    emptyTexture.loadFromFile("Sprites/UI/EmptyHealth.png");
    fullTexture.loadFromFile("Sprites/UI/FullHealth.png");
    coinTexture.loadFromFile("Sprites/UI/Coin.png");
    emptySprite.setTexture(emptyTexture);
    fullSprite.setTexture(fullTexture);
    coinSprite.setTexture(coinTexture);
}

void HealthBar::Update(sf::RenderWindow& window)
{
    for(int i=0;i<Player::getMaxHealth();i++)
    {
        emptySprite.setPosition(i*25+35,40);
        window.draw(emptySprite);
    }
    for(int i=0;i<Player::getHealth();i++)
    {
        fullSprite.setPosition(i*25+35,40);
        window.draw(fullSprite);
    }

    for(int i=0;i<Player::getCoins();i++)
    {
        coinSprite.setPosition(750-i*15,40);
        window.draw(coinSprite);
    }
}