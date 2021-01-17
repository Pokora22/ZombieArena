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
    sound->setBuffer(ResourceManager::Get()->GetSoundBuffer(fileName));
    m_sounds.insert(std::pair<std::string, std::shared_ptr<sf::Sound>> (soundName, sound));
}

void AudioComponent::PlayAudio(const std::string& soundName) {
    auto it = m_sounds.find(soundName);
    if(it != m_sounds.end()) {
        auto &sound = it->second;
        sound->play();
    }else{
        auto it = m_musicTracks.find(soundName);
        if(it != m_musicTracks.end()) {
            Music &track = it->second;
            track.play();
        }
    }
}

void AudioComponent::PauseAudio(const std::string& soundName) {
    auto it = m_sounds.find(soundName);
    if(it != m_sounds.end()) {
        auto &sound = it->second;
        sound->pause();
    }else{
        auto it = m_musicTracks.find(soundName);
        if(it != m_musicTracks.end()) {
            Music &track = it->second;
            track.pause();
        }
    }
}

void AudioComponent::StopAudio(const std::string& soundName) {
    auto it = m_sounds.find(soundName);
    if(it != m_sounds.end()) {
        auto &sound = it->second;
        sound->stop();
    }else{
        auto it = m_musicTracks.find(soundName);
        if(it != m_musicTracks.end()) {
            Music &track = it->second;
            track.stop();
            std::cout << "Stopping music: " << soundName << std::endl;
        }
    }
}

void AudioComponent::AddMusic(const std::string &trackName, const std::string &fileName, bool loop) {
    auto& track = ResourceManager::Get()->GetMusicTrack(fileName);
    track.setLoop(loop);
    m_musicTracks.insert(std::pair<std::string, sf::Music&>(trackName, track));
}