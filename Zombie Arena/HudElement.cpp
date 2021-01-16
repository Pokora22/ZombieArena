//
// Created by pokor on 15/01/2021.
//

#include "HudElement.h"

#include <utility>

HudElement::HudElement(const std::string& fileName, int x, int y) {
    m_Transform = AttachComponent<TransformComponent>();
    m_Sprite = AttachComponent<SpriteComponent>();

    m_Transform->SetPosition(Vector2f(x, y), 0);
    m_Sprite->SetSprite(TextureHolder::GetTexture(fileName), false);
    m_Sprite->setPosition(m_Transform->GetPosition());
}

HudElement::HudElement(const std::string& text, Font &font, float x, float y) {
    m_Text = AttachComponent<TextComponent>();
    setFont(font);
    setText(text);
    setPosition(x, y);
}

void HudElement::setFont(const sf::Font& font) {
    m_Text->setFont(font);
}

void HudElement::setCharacterSize(int size) {
    m_Text->setCharacterSize(size);
}

void HudElement::setFillColor(sf::Color color) {
    m_Text->setFillColor(color);
}

void HudElement::setText(const std::string& text) {
    m_Text->setText(text);
}

void HudElement::setPosition(float x, float y) {
    m_Text->setPosition(x, y);
}

void HudElement::Draw(RenderWindow &window) {
    //TODO: Check if not null
    if(m_Sprite)
        m_Sprite->Draw(window);
    if(m_Text)
        m_Text->Draw(window);
}

void HudElement::SetScale(Vector2f factors) {
    m_Sprite->setScale(factors);
}
