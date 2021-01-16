//
// Created by pokor on 16/01/2021.
//

#include <iostream>
#include <memory>
#include "AudioComponent.h"

AudioComponent::AudioComponent() {

}

void AudioComponent::AddAudio(std::string soundName, std::string fileName) {
    //TODO: Can this be smart? It's retained whole game so not necessary?
    auto m_soundBuffer = new sf::SoundBuffer;
    m_soundBuffer->loadFromFile(fileName);
    std::shared_ptr<sf::Sound> sound(new sf::Sound);
    sound->setBuffer(*m_soundBuffer);
    m_sounds.insert(std::pair<std::string, std::shared_ptr<sf::Sound>> (soundName, sound));
}

void AudioComponent::PlayAudio(std::string soundName) {
    std::cout << "(AudioComponent)Playing: " << soundName << std::endl;
    m_sounds.find(soundName)->second->play();
}

void AudioComponent::PauseAudio(std::string soundName) {
    m_sounds.find(soundName)->second->pause();
}

void AudioComponent::StopAudio(std::string soundName) {
    m_sounds.find(soundName)->second->stop();
}