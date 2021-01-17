//
// Created by Pokora on 26/11/2019.
//

#include "ZombieHorde.h"

bool ZombieHorde::saveConfig(const std::string& filename) {
    nlohmann::json statsString;
    for(auto info : m_zombieStats){
        statsString[info.first] = {
                {"type", info.second.type},
                {"speed", info.second.speed},
                {"health", info.second.health},
                {"damage", info.second.damage},
                {"sprite", info.second.spriteFile}
        };
    }

    nlohmann::json configString = {
            {"speedBase", m_config.baseSpeed},
            {"speedVariance", m_config.speedVariance},
            {"zombieStats", statsString}
    };

    //Open file out
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        // write
        fout << std::setw(4) << statsString << std::endl;
    }
    fout.close();
    return true;
}

bool ZombieHorde::loadConfig(const std::string& filename) {
    std::cout << "Loading config" << std::endl;
    //Open file in
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        std::cout << "failed to open " << filename << '\n';
        return false;
    } else {
        // read
        nlohmann::json jsonString;
        fin >> jsonString;

        jsonString.at("speedVariance").get_to(m_config.speedVariance);
        jsonString.at("speedBase").get_to(m_config.baseSpeed);

        // 3 is placeholder !
        for(int i = 0; i < jsonString.at("zombieStats").size(); i++){
            auto info = jsonString.at("zombieStats")[i];
            m_zombieStats.emplace(i, Stats(info["type"],
                                           info["speed"],
                                           info["health"],
                                           info["damage"],
                                           info["sprite"]));
        }

        m_config.zombieStats = m_zombieStats;
    }

    fin.close();
    return true;
}

Config& ZombieHorde::getConfig() {
    return m_config;
}

ZombieHorde::ZombieHorde(const std::string& filename) {
    if(m_zombieStats.empty())
        loadConfig(filename);
}
