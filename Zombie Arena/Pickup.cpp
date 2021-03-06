//
// Created by Pokora on 21/12/2019.
//

#include "Pickup.h"
#include "ResourceManager.h"

Pickup::Pickup(TYPE type, Vector2f position) : Entity()
{
    m_Audio = AttachComponent<AudioComponent>();

    //store type of pickup (1 - health, 2 - ammo)
    m_Type = type;

    //Associate type with texture
    if(m_Type == 1){
        SetSprite("../Resources/graphics/health_pickup.png");
        m_Audio->AddAudio("pick", "../Resources/sound/pickup.wav");
        //set worth
        m_Value = HEALTH_START_VALUE;
    }
    else{
        SetSprite("../Resources/graphics/ammo_pickup.png");
        m_Audio->AddAudio("pick", "../Resources/sound/reload.wav");

        m_Value = AMMO_START_VALUE;
    }

    SetPosition(position, 0);

    m_SecondsToLive = START_SECONDS_TO_LIVE;
    m_SecondsToWait = START_WAIT_TIME;

    m_Spawned = true;

    Update();
}

void Pickup::setArena(IntRect arena)
{

    // Copy the details of the arena to the pickup's m_Arena
    m_Arena.left = arena.left + 50;
    m_Arena.width = arena.width - 50;
    m_Arena.top = arena.top + 50;
    m_Arena.height = arena.height - 50;

    spawn();
}

void Pickup::spawn()
{
    srand((int)time(0) / m_Type);
    float x = (rand() % m_Arena.width);
    srand((int)time(0) * m_Type);
    float y = (rand() % m_Arena.height);

    SetPosition(Vector2f(x, y), 0);

    m_SecondsSinceSpawn = 0;
    m_Spawned = true;
}

FloatRect Pickup::getPosition()
{
    return m_Sprite->GetSprite().getGlobalBounds();
}

Sprite Pickup::getSprite()
{
    return m_Sprite->GetSprite();
}

bool Pickup::isSpawned()
{
    return m_Spawned;
}

int Pickup::gotIt()
{
    m_Audio->PlayAudio("pick");
    m_Spawned = false;
    m_SecondsSinceDeSpawn = 0;
    return m_Value;
}

void Pickup::update(float elapsedTime)
{
    if(m_Spawned){
        m_SecondsSinceSpawn += elapsedTime;
    }
    else{
        m_SecondsSinceDeSpawn += elapsedTime;
    }

    if(m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned){
        m_Spawned = false;
        m_SecondsSinceDeSpawn = 0;
    }
    if(m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned){
        spawn();
    }

    Update();
}

void Pickup::upgrade()
{
    if(m_Type == 1){
        m_Value += (HEALTH_START_VALUE * .5);
    }
    else{
        m_Value += (AMMO_START_VALUE * .5);
    }

    //Make them last longer and more frequent
    m_SecondsToLive += (START_SECONDS_TO_LIVE * .1);
    m_SecondsToWait -= (START_WAIT_TIME * .1);
}

void Pickup::draw(RenderWindow &window) {
    if(m_Spawned)
        Draw(window);
}
