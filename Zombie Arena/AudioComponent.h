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
    void AddMusic(const std::string& trackName, const std::string& fileName);
    void PlayAudio(const std::string& soundName);
    void PlayMusic(const std::string& trackName, bool loop = true);
    void PauseAudio(const std::string& soundName);
    void PauseMusic(const std::string& trackName);
    void StopAudio(const std::string& soundName);
    void StopMusic(const std::string& trackName);

private:
    std::map<std::string, std::shared_ptr<sf::Sound>> m_sounds;
    std::map<std::string, sf::Music&> m_musicTracks;
};


#endif //ZOMBIEARENA_AUDIOCOMPONENT_H
