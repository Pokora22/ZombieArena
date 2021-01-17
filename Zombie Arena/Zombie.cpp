//
// Created by Pokora on 26/11/2019.
//

#include "Zombie.h"
#include <cstdlib>
#include <cmath>

bool Zombie::hit(int damage) {
    m_Health -= damage;
    if(m_Health <= 0){
        m_Alive = false;
        m_Audio->PlayAudio("splat");
        Entity::SetSprite("../Resources/graphics/blood.png");
    }

    //Return false if still alive
    return !m_Alive;
}

bool Zombie::isAlive() {
    return m_Alive;
}

//TODO: Need default constructor with entity constructor as well?

Zombie::Zombie(int x, int y, ZombieHorde horde) : Entity(){
    int r = rand();
    Config& config = horde.getConfig();
    Stats& stats = config.zombieStats.find(r % 3)->second;

    Entity::SetSprite(stats.spriteFile);
    m_Speed = stats.speed;
    m_Health = stats.health;
    m_Damage = stats.damage;
    m_Type = stats.type;
//
    //Randomize speed to prevent bunching
    float modifier = (r % config.speedVariance) + config.baseSpeed;
    modifier /= 100;
    m_Speed *= modifier;

    std::cout << "Zombie speed: " << config.baseSpeed << std::endl;

    m_Audio = AttachComponent<AudioComponent>();
    m_Audio->AddAudio("explode", "../Resources/sound/pop.ogg");
    m_Audio->AddAudio("splat", "../Resources/sound/splat.wav");

    SetPosition(Vector2f(x, y), 0);
}


FloatRect Zombie::getPosition() {
    return m_Sprite->GetSprite().getGlobalBounds();
}

Sprite Zombie::getSprite() {
    return m_Sprite->GetSprite();
}

void Zombie::update(float elapsedTime, Entity &player, std::vector<Tile*>& walls) {
    float playerX = player.GetPosition().x;
    float playerY = player.GetPosition().y;

    float distanceToPlayer = Distance(player);
    if(distanceToPlayer < 200)
        m_Alerted = true;
    if(distanceToPlayer > 400)
        m_Alerted = false;

    if(m_Alerted) {
        Vector2f origPosition = m_Transform->GetPosition();
        float x = 0, y = 0;
        // Update the zombie position variables
        if (playerX > origPosition.x) {
            x = origPosition.x + m_Speed * elapsedTime;
        }

        if (playerY > origPosition.y) {
            y = origPosition.y + m_Speed * elapsedTime;
        }

        if (playerX < origPosition.x) {
            x = origPosition.x - m_Speed * elapsedTime;
        }

        if (playerY < origPosition.y) {
            y = origPosition.y - m_Speed * elapsedTime;
        }

        // Face the sprite in the correct direction
        float rotation = (atan2(playerY - origPosition.y,
                            playerX - origPosition.x)
                      * 180) / 3.141f;



        for (int i = 0; i < walls.size(); i++)
            if (Collision(*walls[i])) {
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
    }

//    std::cout << "Zombie pos: " << GetPosition().x << " : " << GetPosition().y << std::endl;

    Update();
}

void Zombie::draw(RenderWindow &window) {
    Draw(window);
}

std::pair<int, int> Zombie::OnDeath(Entity &player, std::vector<Tile *> &walls, std::vector<Zombie*>& zombies, int effectDistance) {
    std::pair<int, int> damageAndPoints;
    damageAndPoints.first = 0;
    damageAndPoints.second = 0;

    if(m_Type == "bloater"){
        m_Audio->PlayAudio("explode");

        if(Distance(player) < effectDistance)
            damageAndPoints.first = 30;

        //Destroy nearby walls
        for(auto wall : walls){
            if(Distance(*wall) < effectDistance && !wall->isEdge())
                wall->SetActive(false);
        }

        //Kill nearby zombies and award points
        for(auto zombie : zombies){
            if(Distance(*zombie) < effectDistance){
                if(zombie->hit(5))
                    damageAndPoints.second += 10;
            }
        }
    }

    return damageAndPoints;
}

int Zombie::GetDamage() {
    return m_Damage;
}


void Zombie::spawn(float startX, float startY, int type, int seed) {

}

const std::string& Zombie::GetZombieType() {
    return m_Type;
}
