cmake_minimum_required(VERSION 3.17)
project(ZombieArena)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES "Zombie Arena/")

add_executable(ZombieArena ${SOURCE_FILES}/ZombieArena.cpp
        ${SOURCE_FILES}/player.cpp  ${SOURCE_FILES}/Arena.cpp "Zombie Arena/ResourceManager.cpp"
        "Zombie Arena/ResourceManager.h" "Zombie Arena/Zombie.cpp" "Zombie Arena/Zombie.h" "Zombie Arena/Bullet.cpp"
        "Zombie Arena/Bullet.h" "Zombie Arena/Pickup.cpp" "Zombie Arena/Pickup.h" "Zombie Arena/Entity.h"
        "Zombie Arena/Entity.cpp" "Zombie Arena/Tile.cpp" "Zombie Arena/Tile.h" "Zombie Arena/MazeGenerator.cpp"
        "Zombie Arena/MazeGenerator.h" "Zombie Arena/Flashlight.cpp" "Zombie Arena/Flashlight.h" "Zombie Arena/Key.cpp"
        "Zombie Arena/Key.h" "Zombie Arena/ExitTerminal.cpp" "Zombie Arena/ExitTerminal.h" "Zombie Arena/Grenade.cpp"
        "Zombie Arena/Grenade.h" "Zombie Arena/HudElement.cpp" "Zombie Arena/HudElement.h"
        "Zombie Arena/SpriteComponent.cpp" "Zombie Arena/TransformComponent.cpp"
        "Zombie Arena/Component.cpp" "Zombie Arena/AudioComponent.cpp" "Zombie Arena/AudioComponent.h"
        "Zombie Arena/TextComponent.cpp" "Zombie Arena/TextComponent.h" "Zombie Arena/Hud.cpp" "Zombie Arena/Hud.h"
        "Zombie Arena/ZombieHorde.cpp")

# Detect and add SFML
#set(SFML_DIR "G:/Dokumenty/WIT/Cpp/SFML-2.5.1/lib/cmake/SFML")
#find_package(SFML REQUIRED COMPONENTS system window graphics audio)
#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(ZombieArena sfml-system sfml-window sfml-graphics sfml-audio)
#endif()

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "G:/Dokumenty/WIT/Cpp/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(ZombieArena sfml-audio sfml-graphics sfml-window sfml-system)