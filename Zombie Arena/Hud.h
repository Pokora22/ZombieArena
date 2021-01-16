//
// Created by pokor on 16/01/2021.
//

#ifndef ZOMBIEARENA_HUD_H
#define ZOMBIEARENA_HUD_H


#include "HudElement.h"

class Hud {
public:
    Hud(Vector2f resolution);
    void AddElement(const std::string& name, std::shared_ptr<HudElement> &element);
    void Draw(RenderWindow &window);
    void ChangeText(const std::string& element, const std::string& text);
private:
    std::map<std::string, std::shared_ptr<HudElement>> m_Elements;

};


#endif //ZOMBIEARENA_HUD_H
