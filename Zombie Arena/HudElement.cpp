//
// Created by pokor on 15/01/2021.
//

#include "HudElement.h"

HudElement::HudElement(std::string fileName, int x, int y) : Entity(fileName){
    SetPosition(Vector2f(x, y), 0);
}
