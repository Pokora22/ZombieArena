//
// Created by Pokora on 26/11/2019.
//

#include "ResourceManager.h"
#include <assert.h>

#include <memory>

using namespace sf;
using namespace std;


std::unique_ptr<ResourceManager> ResourceManager::m_s_Instance = nullptr;

Texture& ResourceManager::GetTexture(std::string const &filename) {
    //Get reference of the texture map from this instance
    auto& map = m_s_Instance->m_Textures;

    //Create iterator and search for texture by filename
    auto kvp = map.find(filename);

    //Return texture if found in map
    if(kvp != map.end())
        return kvp->second;
    else{
        //Create new key
        auto& texture = map[filename];

        //Load texture from file into the map and return it
        texture.loadFromFile(filename);
        return texture;
    }
}

SoundBuffer &ResourceManager::GetSoundBuffer(const string &filename) {
    auto& map = m_s_Instance->m_SoundBuffers;

    auto kvp = map.find(filename);

    if(kvp != map.end())
        return kvp->second;
    else{
        auto & sbuffer = map[filename];

        sbuffer.loadFromFile(filename);
        return sbuffer;
    }
}

unique_ptr<ResourceManager> & ResourceManager::Get() {
    if(m_s_Instance == nullptr){
        m_s_Instance = std::make_unique<ResourceManager>();
    }

    return m_s_Instance;
}

Music &ResourceManager::GetMusicTrack(const string &filename) {
    auto& map = m_s_Instance->m_MusicTracks;

    auto kvp = map.find(filename);

    if(kvp != map.end())
        return kvp->second;
    else{
        auto &track = map[filename];

        track.openFromFile(filename);
        return track;
    }
}
