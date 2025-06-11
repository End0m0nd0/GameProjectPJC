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

add_executable(untitled src/main.cpp
        src/Player.cpp
        src/Player.h
        src/Projectile.cpp
        src/Projectile.h
        src/Background.cpp
        src/Background.h
        src/Stage.cpp
        src/Stage.h
        src/Obstacle.cpp
        src/Obstacle.h
        src/Map.cpp
        src/Map.h
        src/Enemy.cpp
        src/Enemy.h
        src/FlyingEnemy.cpp
        src/FlyingEnemy.h
        src/FlyingEnemy.h
        src/EnemyProjectile.cpp
        src/EnemyProjectile.h
        src/HealthBar.cpp
        src/HealthBar.h
        src/Turret.cpp
        src/Turret.h
        src/Turret.h
        src/EnemyVector.cpp
        src/EnemyVector.h
        src/EnemyVector.h
        src/HumanEnemy.cpp
        src/HumanEnemy.h
        src/Directions.cpp
        src/Directions.h
        src/RobotEnemy.cpp
        src/RobotEnemy.h
        src/CollectItem.cpp
        src/CollectItem.h
        src/CollectableVector.cpp
        src/CollectableVector.h
        src/UpgradeMenu.cpp
        src/UpgradeMenu.h
        src/Menu.cpp
        src/Menu.h
        src/Path.cpp
        src/Path.h
)
target_link_libraries(untitled sfml-graphics)