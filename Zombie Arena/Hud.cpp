//
// Created by pokor on 16/01/2021.
//

#include "Hud.h"

Hud::Hud(Vector2f resolution) {
//    TODO: Causes segmentation fault when accessing text elements
    Font zombieFont, labFont;
    zombieFont.loadFromFile("../Resources/fonts/zombiecontrol.ttf");
    labFont.loadFromFile("../Resources/fonts/xirod.ttf");

    std::shared_ptr<HudElement> ammoIcon(new HudElement("../Resources/graphics/ammo_icon.png",
                                                        20, resolution.y - 200));
    AddElement("ammoIcon", ammoIcon);

    std::shared_ptr<HudElement> grenadeIcon(new HudElement("../Resources/graphics/grenade.png",
                                                           420, resolution.y - 200));
    grenadeIcon->SetScale(Vector2f(3, 3));
    AddElement("grenadeIcon", grenadeIcon);

    std::shared_ptr<HudElement> ammoText(new HudElement("ammo", 150, resolution.y - 200,
                                                        zombieFont, 55));
    AddElement("ammo", ammoText);

    std::shared_ptr<HudElement> grenadeCount(new HudElement("grenades", 570, resolution.y - 200,
                                                        zombieFont, 55));
    AddElement("grenades", grenadeCount);

    std::shared_ptr<HudElement> scoreText(new HudElement("score", 20, 0, zombieFont, 55));
    AddElement("score", scoreText);

    std::shared_ptr<HudElement> hiscoreText(new HudElement("hiscore", resolution.x - 400, 0,
                                                           zombieFont, 55));
    AddElement("hiscore", hiscoreText);

    std::shared_ptr<HudElement> keysCollected(new HudElement("keys", resolution.x - 400, resolution.y - 200,
                                                             zombieFont, 55));
    AddElement("keys", keysCollected);

    std::shared_ptr<HudElement> timeLeft(new HudElement("timeleft", resolution.x * 0.66, resolution.y - 200,
                                                             zombieFont, 55));
    AddElement("timeleft", timeLeft);
}

void Hud::Draw(RenderWindow &window) {
    for(auto& e : m_Elements){
        e.second->Draw(window);
    }
}

void Hud::ChangeText(const std::string& element, const std::string& text) {
    m_Elements.find(element)->second->setText(text);
}

void Hud::AddElement(const std::string& name, std::shared_ptr<HudElement> &element) {
    m_Elements.insert(std::pair<std::string, std::shared_ptr<HudElement>>(name, element));
}

