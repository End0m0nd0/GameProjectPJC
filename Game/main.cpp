#include <SFML/Graphics.hpp>
#include <iostream>
#include "Projectile.h"
#include "Background.h"
#include "HealthBar.h"
#include "UpgradeMenu.h"
#include "Map.h"
#include "EnemyVector.h"
#include "CollectableVector.h"
#include "Menu.h"

void resetAll();
Player player;
Menu menu;
UpgradeMenu upgradeMenu;
Map map;
HealthBar healthBar;
CollectableVector collectableVector;
EnemyVector enemyVector;

auto main() -> int {
    int cheat=0;
    auto window = sf::RenderWindow(
            sf::VideoMode({800, 800}), "Game",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );

    window.setFramerateLimit(144);

    while (window.isOpen()) {
        window.clear(sf::Color::Black);


        if(!upgradeMenu.getIsActive()&&!menu.getIsActive()) {

            map.getCurrentStage().drawBg(window);
            player.update(map.getCurrentStage());
            window.draw(player.player());
            enemyVector.updateWalking(window);
            map.getCurrentStage().updateOb(window);
            map.drawWalls(window);
            for (Projectile &projectile: Player::getProjectiles())
                projectile.update(window);
            collectableVector.update(window);
            enemyVector.updateFlying(window);


            for (EnemyProjectile &enemyProjectile: Enemy::getEnemyProjectiles()) {
                enemyProjectile.update(window);
            }
            healthBar.Update(window);

            ///////////////Usuwanie z pamieci pocisków///////////////
            for(auto it = Enemy::getEnemyProjectiles().begin();it<Enemy::getEnemyProjectiles().end();it++)
                if((*it).getX()>900||(*it).getX()<-100||(*it).getY()>900||(*it).getY()<-100)
                    Enemy::getEnemyProjectiles().erase(it);

            for(auto it = Player::getProjectiles().begin();it<Player::getProjectiles().end();it++)
                if((*it).getX()>900||(*it).getX()<-100||(*it).getY()>900||(*it).getY()<-100)
                    Player::getProjectiles().erase(it);
            ///////////////Usuwanie z pamieci pocisków///////////////


            ///////////////Otwieranie skrzynni///////////////
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                for (Obstacle &obstacle: map.getCurrentStage().vec) {
                    if (obstacle.open(player.player())){
                        collectableVector.add(obstacle.getX() + 0, obstacle.getY() + 30);
                        collectableVector.add(obstacle.getX() + 30, obstacle.getY() + 30);
                        collectableVector.add(obstacle.getX() + 60, obstacle.getY() + 30);
                        }
                }
            }
            ///////////////Otwieranie skrzynni///////////////

            if(Player::getIsDead()){
                menu.lost(Player::getStagesCleared());
                resetAll();
            }

            if(Map::didWin())
            {
                menu.lost(100);
                resetAll();
            }

            auto event = sf::Event();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (!player.getIsCurrentlyShooting()) {
                        sf::Vector2 mousePosition = sf::Mouse::getPosition(window);
                        int direction;
                        bool goUpOrDown;
                        if (fabs(mousePosition.x - Player::getX()) > fabs(mousePosition.y - Player::getY()))
                            goUpOrDown = false;
                        else goUpOrDown = true;
                        if (mousePosition.x < Player::getX())
                            player.lookLeft();

                        else
                            player.lookRight();
                        if (mousePosition.x < Player::getX() && !goUpOrDown) direction = 1;
                        else if (mousePosition.x > Player::getX() && !goUpOrDown) direction = 3;
                        else if (mousePosition.y < Player::getY() && goUpOrDown) direction = 2;
                        else direction = 4;

                        if(Player::player().getScale().x>0)
                        Player::add(Projectile(Player::getX()+Player::getSpriteWidth()/2, Player::getY()+Player::getSpriteHeight()/2, direction));
                        else
                        Player::add(Projectile(Player::getX()-Player::getSpriteWidth()/2, Player::getY()+Player::getSpriteHeight()/3, direction));
                        player.shoot();
                    }
                }
                if(event.type==sf::Event::KeyPressed)
                    if(event.key.code==sf::Keyboard::Tab) {
                        upgradeMenu.changeIsActive();
                        upgradeMenu.openUpgrades();
                    }
                else if(event.key.code==sf::Keyboard::M) {
                        upgradeMenu.changeIsActive();
                        upgradeMenu.openMinimap();
                    }
                //code
                if(event.type==sf::Event::KeyPressed)
                    if(event.key.code==sf::Keyboard::P) {
                        if (cheat == 0)
                            cheat++;
                        else cheat=0;
                    }
                else if(event.key.code==sf::Keyboard::J)
                    {
                        if(cheat==1)
                            cheat++;
                        else cheat=0;
                    }
                    else if(event.key.code==sf::Keyboard::A)
                    {
                        if(cheat==2)
                            cheat++;
                        else cheat=0;
                    }
                    else if(event.key.code==sf::Keyboard::T)
                    {
                        if(cheat==3)
                            cheat++;
                        else cheat=0;
                    }
                    else if(event.key.code==sf::Keyboard::K)
                    {
                        if(cheat==4) {
                            Player::cheat();
                            cheat=0;
                        }
                    }
                    else cheat=0;
            }
        }
        else if(menu.getIsActive()){
            menu.update(window);
        }
        else if(upgradeMenu.getIsActive()){
            upgradeMenu.update(window,player,enemyVector,map,collectableVector,healthBar);
        }

        window.display();
    }
}
void resetAll()
{
    Map::resetStatics();
    CollectableVector::resetStatics();
    Enemy::resetStatics();
    EnemyProjectile::resetStatics();
    EnemyVector::resetStatics();
    Player::resetStatics();
    upgradeMenu = UpgradeMenu();
    map.createNew();
    enemyVector.createNew();
}