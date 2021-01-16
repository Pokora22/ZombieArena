//
// Created by Pokora on 28/12/2019.
//

#include <cmath>
#include "Entity.h"

Entity::Entity(const std::string &filename) : Object() {
    m_Sprite = AttachComponent<SpriteComponent>();
    m_Transform = AttachComponent<TransformComponent>();
    m_active = true;
    SetSprite(filename);
}

Entity::Entity(const std::string &filename, int x, int y) : Object() {
    m_Sprite = AttachComponent<SpriteComponent>();
    m_Transform = AttachComponent<TransformComponent>();
    m_active = true;
    m_Transform->SetPosition(sf::Vector2f(x, y), 0);

    SetSprite(filename);
}

Entity::Entity() : Object() {
    m_Sprite = AttachComponent<SpriteComponent>();
    m_Transform = AttachComponent<TransformComponent>();
    m_active = true;
}

void Entity::Draw(RenderWindow &window){
    if(m_active)
        m_Sprite->Draw(window);
}

bool Entity::Collision(Entity& entity)
{
    sf::FloatRect ownBounds = m_Sprite->GetSprite().getGlobalBounds();
    sf::FloatRect colliderBounds = entity.GetSprite().getGlobalBounds();

    bool collision = m_active && entity.isActive() && ownBounds.intersects(colliderBounds);
    if(collision){
        float x = GetPosition().x;
        float y = GetPosition().y;

        float ex = entity.GetPosition().x;
        float ey = entity.GetPosition().y;

//        std::cout << "(Entity.cpp::Collision)Position: " << GetPosition().x << " : " << GetPosition().y << std::endl;
//
//        std::cout << "(Entity.cpp::Collision)Ownbounds: (" << ownBounds.left << ", " << ownBounds.top <<
//            ", " << ownBounds.left + ownBounds.width << ", "  << ownBounds.top + ownBounds.height << ")" << std::endl;

//        std::cout << "(Entity.cpp::Collision)colliderBounds: (" << colliderBounds.left << ", " << colliderBounds.top <<
//                  ", " << colliderBounds.left + colliderBounds.width << ", "  <<
//                  colliderBounds.top + colliderBounds.height << ")" << std::endl;

//        std::cout << "(Entity.cpp::Collision)Org pos: " << x << " : " << y << " -- "
//                  << "Wall: " << ex << " : " << ey << std::endl;
    }

    return m_active && entity.isActive() && ownBounds.intersects(colliderBounds);
}

void Entity::SetActive(bool active)
{
    m_active = active;
}

int Entity::GetActive() {
    return m_active;
}

int Entity::GetGroup() {
    return m_group_id;
}

Sprite Entity::GetSprite() {
    return m_Sprite->GetSprite();
}

void Entity::SetSprite(const std::string filename) {
    m_Sprite->SetSprite(ResourceManager::GetTexture(filename));

    Update();
}

void Entity::SetPosition(Vector2f position, float angle) {
    m_Transform->SetPosition(position, angle);
    m_Sprite->setPosition(position);
}

void Entity::Update() {
    m_Sprite->setPosition(GetPosition(), m_Transform->GetRotation());
}

float Entity::Distance(Entity &entity) {
    Vector2f ownPos = GetPosition();
    Vector2f entityPos = entity.GetPosition();
    return sqrt(pow((ownPos.y - entityPos.y), 2) + pow((ownPos.x - entityPos.x), 2));
}

Vector2f Entity::GetPosition() {
    return m_Transform->GetPosition();
}

float Entity::GetRotation() {
    return m_Transform->GetRotation();
}

bool Entity::isActive() {
    return m_active;
}

void Entity::SetScale(Vector2f factors) {
    m_Sprite->setScale(factors);
}
