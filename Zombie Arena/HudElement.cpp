//
// Created by pokor on 15/01/2021.
//

#include "HudElement.h"

#include <utility>

HudElement::HudElement(const std::string& fileName, int x, int y) {
    m_Sprite = AttachComponent<SpriteComponent>();
    m_Sprite->SetSprite(TextureHolder::GetTexture(fileName));
    m_Transform->SetPosition(Vector2f(x, y), 0);
}

HudElement::HudElement(const std::string& text, Font &font, float x, float y) {
    setFont(font);
    setText(text);
    setPosition(x, y);
}

void HudElement::setFont(const sf::Font& font) {
    m_Text.setFont(font);
}

void HudElement::setCharacterSize(int size) {
    m_Text.setCharacterSize(size);
}

void HudElement::setFillColor(sf::Color color) {
    m_Text.setFillColor(color);
}

void HudElement::setText(const std::string& text) {
    m_Text.setString(text);
}

void HudElement::setPosition(float x, float y) {
    m_Text.setPosition(x, y);
}

void HudElement::Draw(RenderWindow &window) {
    m_Sprite->Draw(window);
    //TODO: Draw text?
}

void HudElement::SetScale(Vector2f factors) {
    m_Sprite->setScale(factors);
}
