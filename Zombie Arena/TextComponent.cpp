//
// Created by pokor on 16/01/2021.
//

#include "TextComponent.h"

void TextComponent::setText(const std::string &text) {
    m_Text.setString(text);
}

void TextComponent::setFont(const sf::Font &font) {
    m_Text.setFont(font);
}

void TextComponent::setCharacterSize(int size) {
    m_Text.setCharacterSize(size);
}

void TextComponent::setFillColor(sf::Color color) {
    m_Text.setFillColor(color);
}

void TextComponent::setPosition(float x, float y) {
    m_Text.setPosition(x, y);
}

void TextComponent::Draw(sf::RenderWindow &window) {
    window.draw(m_Text);
}