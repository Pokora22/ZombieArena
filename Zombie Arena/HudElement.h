//
// Created by pokor on 15/01/2021.
//

#ifndef ZOMBIEARENA_HUDELEMENT_H
#define ZOMBIEARENA_HUDELEMENT_H

#include "Entity.h"
#include "TextComponent.h"

class HudElement : public Object{
public:
    HudElement(const std::string& fileName, int x, int y);
    HudElement(const std::string& text, sf::Font &font, float x, float y);
    void setText(const std::string& text);
    void setFont(const sf::Font& font);
    void setCharacterSize(int size);
    void setFillColor(sf::Color color);
    void setPosition(float x, float y);

    void Draw(RenderWindow &window);

    void SetScale(Vector2f factors);

private:
    std::shared_ptr<TransformComponent> m_Transform;
    std::shared_ptr<SpriteComponent> m_Sprite;
    std::shared_ptr<TextComponent> m_Text;
};


#endif //ZOMBIEARENA_HUDELEMENT_H
