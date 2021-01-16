//
// Created by Pokora on 26/11/2019.
//

#include "ResourceManager.h"
#include <assert.h>

using namespace sf;
using namespace std;

ResourceManager* ResourceManager::m_s_Instance = nullptr;

ResourceManager::ResourceManager() {
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

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