#include "stdafx.h"
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
	if (m_HitboxComponent)
		m_HitboxComponent->setPosition(x, y);
	else
		m_Sprite.setPosition(x, y);
}


const sf::Vector2f& Entity::getPosition() const
{
	if (m_HitboxComponent)
		return m_HitboxComponent->getPosition();

	return m_Sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (m_HitboxComponent)
		return m_HitboxComponent->getGlobalBounds();
	
	return m_Sprite.getGlobalBounds();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (m_HitboxComponent)
		return sf::Vector2u(
			static_cast<unsigned>(m_HitboxComponent->getPosition().x) / gridSizeU, 
			static_cast<unsigned>(m_HitboxComponent->getPosition().y) / gridSizeU
		);

	return sf::Vector2u(
		static_cast<unsigned>(m_Sprite.getPosition().x) / gridSizeU,
		static_cast<unsigned>(m_Sprite.getPosition().y) / gridSizeU
	);
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (m_HitboxComponent && m_MovementComponent)
		return m_HitboxComponent->getNextPosition(m_MovementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::stopVelocity()
{
	if (m_MovementComponent)
		m_MovementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (m_MovementComponent)
		m_MovementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (m_MovementComponent)
		m_MovementComponent->stopVelocityY();
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
