//
// Created by pokor on 16/01/2021.
//

#include "TextComponent.h"

void TextComponent::setText(const std::string &text) {
    m_Text.setString(text);
    Center();
}

void TextComponent::setFont(const sf::Font &font) {
    m_Text.setFont(font);
    Center();
}

void TextComponent::setCharacterSize(int size) {
    m_Text.setCharacterSize(size);
    Center();
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

TextComponent::TextComponent() {

}

void TextComponent::Center() {
    //Update origin on text changes
    sf::FloatRect bounds = m_Text.getLocalBounds();
    m_Text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

sf::String TextComponent::getText() {
    return (m_Text.getString());
}


