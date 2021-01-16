//
// Created by pokor on 16/01/2021.
//

#include <iostream>
#include <memory>
#include "AudioComponent.h"
#include "ResourceManager.h"

AudioComponent::AudioComponent() {

}

void AudioComponent::AddAudio(const std::string& soundName, const std::string& fileName) {
    std::shared_ptr<sf::Sound> sound(new sf::Sound);
    sound->setBuffer(ResourceManager::GetSoundBuffer(fileName));
    m_sounds.insert(std::pair<std::string, std::shared_ptr<sf::Sound>> (soundName, sound));
}

void AudioComponent::PlayAudio(const std::string& soundName) {
    m_sounds.find(soundName)->second->play();
}

void AudioComponent::PauseAudio(const std::string& soundName) {
    m_sounds.find(soundName)->second->pause();
}

void AudioComponent::StopAudio(const std::string& soundName) {
    m_sounds.find(soundName)->second->stop();
}