//
// Created by pokor on 16/01/2021.
//

#ifndef ZOMBIEARENA_HUD_H
#define ZOMBIEARENA_HUD_H


#include "HudElement.h"

class Hud {
public:
    void AddElement(HudElement &element);
    void Draw(RenderWindow &window);

private:
    std::vector<HudElement> m_Elements;
};


#endif //ZOMBIEARENA_HUD_H
