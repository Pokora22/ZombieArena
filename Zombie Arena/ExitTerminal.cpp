//
// Created by Pokora on 02/01/2020.
//

#include "ExitTerminal.h"

void ExitTerminal::Update(float elapsedTime) {
    m_TimeSinceActivation += elapsedTime;
    if(!m_counting && (m_TimeSinceActivation > SCREEN_TIME))
        SetSprite("../Resources/graphics/terminal.png");
}

bool ExitTerminal::ActivateExit(bool hasEnoughKeys) {
    m_Audio->PlayAudio("keyboard");
    if(hasEnoughKeys){
        m_counting = true;
        SetSprite("../Resources/graphics/terminal_alarm.png");
        return true;
    } else{
        m_Audio->PlayAudio("alarm");
        m_TimeSinceActivation = 0;
        SetSprite("../Resources/graphics/terminal_denied.png");
        return false;
    }
}

ExitTerminal::ExitTerminal(int x, int y) {
    m_Audio = AttachComponent<AudioComponent>();
    m_Audio->AddAudio("alarm", "../Resources/sound/alarm.ogg");
    m_Audio->AddAudio("keyboard", "../Resources/sound/keyboard.ogg");

    SetPosition(Vector2f(x, y), 0);
    m_counting = false;
    m_TimeSinceActivation = 0;
    SetSprite("../Resources/graphics/terminal.png");

    Entity::Update();
}
