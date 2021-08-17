#include "Entity.h"

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete m_MovementComponent;
	delete m_AnimationComponent;
	delete m_HitboxComponent;
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(m_Sprite);

	if (m_HitboxComponent)
		m_HitboxComponent->render(target);
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

void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
	m_AnimationComponent = new AnimationComponent(m_Sprite, textureSheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float offsetx, const float offsety, float width, float height)
{
	m_HitboxComponent = new HitboxComponent(sprite, offsetx, offsety, width, height);
}

void Entity::initVariables()
{
	m_MovementComponent = NULL;
	m_AnimationComponent = NULL;
	m_HitboxComponent = NULL;
}
