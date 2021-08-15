#include "Entity.h"

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete m_MovementComponent;
}

void Entity::update(const float& dt)
{
	if (m_MovementComponent)
		m_MovementComponent->update(dt);
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(m_Sprite);
}

void Entity::move(const float x, const float y, const float& dt)
{
	if (m_MovementComponent)
	{
		m_MovementComponent->move(x, y, dt);
	}
}

void Entity::setPosition(const float x, const float y)
{
	m_Sprite.setPosition(x, y);
}


void Entity::setTexture(sf::Texture& texture)
{
	m_Sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	m_MovementComponent = new MovementComponent(m_Sprite, maxVelocity, acceleration, deceleration);
}

void Entity::initVariables()
{
	m_MovementComponent = NULL;
}
