//
// Created by pokor on 16/01/2021.
//

#include "AudioComponent.h"

AudioComponent::AudioComponent() {

}

void AudioComponent::AddAudio(std::string &soundName, std::string &fileName) {
    m_soundBuffer.loadFromFile(fileName);
    std::shared_ptr<sf::Sound> sound;
    sound->setBuffer(m_soundBuffer);
    m_sounds.insert(std::pair<std::string, sf::Sound&> (soundName, *sound));
}

void AudioComponent::PlayAudio(std::string &soundName) {
    m_sounds.find(soundName)->second.play();
}

void AudioComponent::PauseAudio(std::string &soundName) {
    m_sounds.find(soundName)->second.pause();
}

void AudioComponent::StopAudio(std::string &soundName) {
    m_sounds.find(soundName)->second.stop();
}