//
// Created by JEDREK on 19.04.2024.
//

#include "Stage.h"
Stage::Stage (bool firstStage)
{
    {
        bg = Background();
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(0, 4);
        for (int i = 0; i < 8; i++)
            for (auto & obstacle : obstacles)
                obstacle[i] = 0;
        design = distribution(generator);
        distribution = std::uniform_int_distribution<int>(1, 5);
        if(!firstStage)
            switch (design) {
                case 0:
                    obstacles[1][1] = distribution(generator);
                    obstacles[1][3] = distribution(generator);
                    obstacles[1][4] = distribution(generator);
                    obstacles[1][6] = distribution(generator);
                    obstacles[3][3] = distribution(generator);
                    obstacles[3][4] = distribution(generator);
                    obstacles[4][3] = distribution(generator);
                    obstacles[4][4] = distribution(generator);
                    obstacles[6][1] = distribution(generator);
                    obstacles[6][3] = distribution(generator);
                    obstacles[6][4] = distribution(generator);
                    obstacles[6][6] = distribution(generator);
                    break;
                case 1:
                    obstacles[1][1] = distribution(generator);
                    obstacles[2][2] = distribution(generator);
                    obstacles[1][6] = distribution(generator);
                    obstacles[2][5] = distribution(generator);
                    obstacles[6][1] = distribution(generator);
                    obstacles[5][2] = distribution(generator);
                    obstacles[5][5] = distribution(generator);
                    obstacles[6][6] = distribution(generator);
                    break;
                case 2:
                    for (int i = 1; i < 7; i++) {
                        obstacles[i][1] = distribution(generator);;
                        obstacles[i][3] = distribution(generator);
                        obstacles[i][4] = distribution(generator);
                        obstacles[i][6] = distribution(generator);
                    }
                    break;
                case 3:
                    for (int i = 1; i < 7; i++)
                        obstacles[4][i] = distribution(generator);
                    obstacles[1][1] = distribution(generator);
                    obstacles[2][3] = distribution(generator);
                    obstacles[2][4] = distribution(generator);
                    obstacles[1][6] = distribution(generator);
                    obstacles[6][1] = distribution(generator);
                    obstacles[6][6] = distribution(generator);
                    break;
                case 4:
                    if (rand() % 2 == 0) {
                        obstacles[4][4] = 6;
                        obstacles[3][3] = 6;
                    } else {
                        obstacles[4][3] = 6;
                        obstacles[3][4] = 6;
                    }
                    break;
            }
        for (int i = 0; i < 8; i++)
            for (int n = 0; n < 8; n++)
                if (obstacles[i][n] != 0)
                    vec.push_back(Obstacle(obstacles[i][n], 80 + 80 * n, 80 + 80 * i));

    }
}

void Stage::drawBg(sf::RenderWindow& window)
{
    bg.draw(window);
}
void Stage::updateOb(sf::RenderWindow& window)
{
    for(Obstacle& ob : vec)
    {
        ob.update();
        ob.draw(window);
    }
}

void Stage::drawOb(sf::RenderWindow& window)
{
    for(Obstacle& ob : vec)
        ob.draw(window);
}


bool Stage::getIsCleared()
{
    return isCleared;
}

void Stage::clear()
{
    isCleared = true;
}