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

    void AddAudio(std::string soundName, std::string fileName);
    void PlayAudio(std::string soundName);
    void PauseAudio(std::string soundName);
    void StopAudio(std::string soundName);

private:
    sf::SoundBuffer m_soundBuffer;
    std::map<std::string, sf::Sound> m_sounds;
};


#endif //ZOMBIEARENA_AUDIOCOMPONENT_H
