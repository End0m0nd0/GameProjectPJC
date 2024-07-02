cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(untitled main.cpp
        Player.cpp
        Player.h
        Projectile.cpp
        Projectile.h
        Background.cpp
        Background.h
        Stage.cpp
        Stage.h
        Obstacle.cpp
        Obstacle.h
        Map.cpp
        Map.h
        Enemy.cpp
        Enemy.h
        FlyingEnemy.cpp
        FlyingEnemy.h
        FlyingEnemy.h
        EnemyProjectile.cpp
        EnemyProjectile.h
        HealthBar.cpp
        HealthBar.h
        Turret.cpp
        Turret.h
        Turret.h
        EnemyVector.cpp
        EnemyVector.h
        EnemyVector.h
        HumanEnemy.cpp
        HumanEnemy.h
        Directions.cpp
        Directions.h
        RobotEnemy.cpp
        RobotEnemy.h
        CollectItem.cpp
        CollectItem.h
        CollectableVector.cpp
        CollectableVector.h
        UpgradeMenu.cpp
        UpgradeMenu.h
        Menu.cpp
        Menu.h
)
target_link_libraries(untitled sfml-graphics)