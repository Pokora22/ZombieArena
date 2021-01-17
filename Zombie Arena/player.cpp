//
//  Player.cpp
//  Zombie Arena
//

//#include "stdafx.h" // <- Visual Studio only
#include "player.hpp"
#include "ResourceManager.h"

#include <iostream>

Player::Player() : Entity("../Resources/graphics/player.png")
{
//    "../Resources/sound/shoot.wav"
    m_Audio = AttachComponent<AudioComponent>();
//    Add audio clips
    m_Audio->AddAudio("shoot", "../Resources/sound/shoot.wav");
    m_Audio->AddAudio("hit", "../Resources/sound/hit.wav");
    m_Audio->AddAudio("reload", "../Resources/sound/reload.wav");
    m_Audio->AddAudio("reload_failed", "../Resources/sound/reload_failed.wav");
    m_Audio->AddAudio("powerup", "../Resources/sound/powerup.wav");
    m_Audio->AddAudio("explosion", "../Resources/sound/explosion.ogg");
    //Music attached to player cause lazy
    m_Audio->AddMusic("music_ambient", "../Resources/sound/ambient.ogg");
    m_Audio->AddMusic("music_alarmed", "../Resources/sound/alarmed.ogg");

    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;

    m_active = false;

    SetPosition(Vector2f(-1000, -1000), 0);
}

void Player::spawn(int x, int y, Vector2f resolution) {
    // Place the player in the middle of the arena
    SetPosition(Vector2f(x, y), 0);

    m_active = true;

    // Store the resolution for future use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
    return m_LastHit;
}

bool Player::hit(Time timeHit, int damage)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)// 2 tenths of second
    {
        m_LastHit = timeHit;
        m_Health -= damage;
        return true;
    }
    else
    {
        return false;
    }

}

FloatRect Player::getPosition()
{
    return getSprite().getGlobalBounds();
}

Vector2f Player::getCenter()
{
    return Entity::GetPosition();
}

float Player::getRotation()
{
    return Entity::GetRotation();
}

Sprite Player::getSprite()
{
    return Entity::GetSprite();
}

int Player::getHealth()
{
    return m_Health;
}

void Player::setMoveRight(bool right) {
    m_RightPressed = right;
}

void Player::setMoveLeft(bool left) {
    m_LeftPressed = left;
}

void Player::setMoveDown(bool down) {
    m_DownPressed = down;
}

void Player::setMoveUp(bool up) {
    m_UpPressed = up;
}

void Player::update(float elapsedTime, Vector2i mousePosition, std::vector<Tile *> &walls)
{
    if(!m_active)
        return;

    Vector2f origPosition = m_Transform->GetPosition();
    float x = 100, y = 100;

    //Since true is 1 and false is 0 we can calculate displacement by subtracting opposite values multiplied by the booleans
    x = origPosition.x + (m_Speed * m_RightPressed - m_Speed * m_LeftPressed) * elapsedTime;
    y = origPosition.y + (m_Speed * m_DownPressed - m_Speed * m_UpPressed) * elapsedTime;

    // Calculate the angle the player is facing
    float rotation = (atan2(mousePosition.y - m_Resolution.y / 2,
                        mousePosition.x - m_Resolution.x / 2)
                  * 180) / 3.141;

    for(int i = 0; i < walls.size(); i++)
        if(Collision(*walls[i])){
            //If destination would collide with wall, push player back by 1 pixel in a direction from that wall to the player
            float xdif = GetPosition().x - walls[i]->GetPosition().x;
            float ydif = GetPosition().y - walls[i]->GetPosition().y;

            auto playerSize = GetSprite().getLocalBounds().width;

            if(abs(xdif) > playerSize)
                x = origPosition.x + xdif/abs(xdif);
            if(abs(ydif) > playerSize)
                y = origPosition.y + ydif/abs(ydif);
        }

    Entity::SetPosition(Vector2f(x, y), rotation);

    Update();
}

void Player::draw(RenderWindow &window) {
    Entity::Draw(window);
}

void Player::upgradeSpeed()
{
    // 20% speed upgrade
    m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
    // 20% max health upgrade
    m_MaxHealth += (START_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount)
{
    m_Health += amount;

    // But not beyond the maximum
    if (m_Health > m_MaxHealth)
    {
        m_Health = m_MaxHealth;
    }
}

bool Player::isHurt() {
    return m_Health < m_MaxHealth;
}

//Lazy implementation TODO: Where should this go?
void Player::playAudio(const std::string &name) {
    m_Audio->PlayAudio(name);
}

void Player::stopAudio(const std::string &name){
    m_Audio->StopAudio(name);
}
