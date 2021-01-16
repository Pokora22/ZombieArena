//
// Created by pokor on 16/01/2021.
//

#ifndef ZOMBIEARENA_TEXTCOMPONENT_H
#define ZOMBIEARENA_TEXTCOMPONENT_H


#include <SFML/Graphics.hpp>
#include "Component.h"

class TextComponent : public Component{
public:
    TextComponent();

    void setText(const std::string& text);
    void setFont(const sf::Font& font);
    void setCharacterSize(int size);
    void setFillColor(sf::Color color);
    void setPosition(float x, float y);

    sf::String getText();

    void Draw(sf::RenderWindow &window);

    void SetScale(sf::Vector2f factors);

private:
    void Center();

    sf::Text m_Text;
};


#endif //ZOMBIEARENA_TEXTCOMPONENT_H
