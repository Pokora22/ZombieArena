//
// Created by Pokora on 26/11/2019.
//

#ifndef ZOMBIEARENA_RESOURCEMANAGER_H
#define ZOMBIEARENA_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>

using namespace sf;

class ResourceManager {
public:
    static std::unique_ptr<ResourceManager> &Get();
    static Texture& GetTexture(std::string const& filename);
    static SoundBuffer& GetSoundBuffer(const std::string &filename);

private:
    //map of textures and corresponding filenames
    std::map<std::string, sf::Texture> m_Textures;
    std::map<std::string, sf::SoundBuffer> m_SoundBuffers;

    //Pointer to the singleton
    static std::unique_ptr<ResourceManager> m_s_Instance;
};


#endif //ZOMBIEARENA_RESOURCEMANAGER_H
