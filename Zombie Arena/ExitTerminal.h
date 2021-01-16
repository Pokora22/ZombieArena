//
// Created by Pokora on 02/01/2020.
//

#ifndef ZOMBIEARENA_EXITTERMINAL_H
#define ZOMBIEARENA_EXITTERMINAL_H


#include "Tile.h"
#include "AudioComponent.h"

class ExitTerminal : public Entity{
private:
    const int SCREEN_TIME = 3;
    float m_TimeSinceActivation;
    bool m_counting;
    bool m_denied;

    std::shared_ptr<AudioComponent> m_Audio;

public:
    ExitTerminal(int x, int y);
    void Update(float elapsedTime);
    bool ActivateExit(bool hasEnoughKeys);
};


#endif //ZOMBIEARENA_EXITTERMINAL_H
