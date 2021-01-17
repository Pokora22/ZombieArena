//
// Created by Pokora on 26/11/2019.
//

#ifndef ZOMBIEARENA_ZOMBIEHORDE_H
#define ZOMBIEARENA_ZOMBIEHORDE_H

#include "Zombie.h"
#include <assert.h>
#include <fstream>
#include <iomanip>
#include "nlohmann/json.hpp"

struct Stats{
    Stats(std::string type, float speed, float health, float damage, std::string spriteFile){
        this->type = type;
        this->speed = speed;
        this->health = health;
        this->damage = damage;
        this->spriteFile = spriteFile;
    }
    std::string type;
    float speed;
    float health;
    float damage;
    std::string spriteFile;
};

struct Config{
    int baseSpeed, speedVariance;
    std::map<int, Stats> zombieStats;
};

class ZombieHorde {
public:
    Config& getConfig();
    bool saveConfig(const std::string& filename);
    bool loadConfig(const std::string& filename);
private:
    std::map<int, Stats> m_zombieStats;
    Config m_config;
};


#endif //ZOMBIEARENA_ZOMBIEHORDE_H
