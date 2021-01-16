//
// Created by Pokora on 02/01/2020.
//

#include "Key.h"

Key::Key(int x, int y) : Entity(){
    m_Audio = AttachComponent<AudioComponent>();
    m_Audio->AddAudio("pick", "../Resources/sound/keycard.ogg");

    SetSprite("../Resources/graphics/keycard.png");

    SetPosition(Vector2f(x, y), 0);

    m_collected = false;

    Update();
}

void Key::Collect() {
    m_Audio->PlayAudio("pick");
    m_collected = true;
}

bool Key::isCollected() {
    return m_collected;
}

void Key::Draw(RenderWindow& window) {
    if(!m_collected)
        Entity::Draw(window);
}
