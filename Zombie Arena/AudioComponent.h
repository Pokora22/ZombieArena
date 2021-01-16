//
// Created by pokor on 16/01/2021.
//

#ifndef ZOMBIEARENA_AUDIOCOMPONENT_H
#define ZOMBIEARENA_AUDIOCOMPONENT_H

#include "Component.h"
#include <SFML/Audio.hpp>
#include <map>
#include <memory>

class AudioComponent : public Component {
public:
    AudioComponent();

    void AddAudio(const std::string& soundName, const std::string& fileName);
    void PlayAudio(const std::string& soundName);
    void PauseAudio(const std::string& soundName);
    void StopAudio(const std::string& soundName);

private:
    std::map<std::string, std::shared_ptr<sf::Sound>> m_sounds;
};


#endif //ZOMBIEARENA_AUDIOCOMPONENT_H
