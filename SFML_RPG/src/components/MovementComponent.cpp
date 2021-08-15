#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: m_Sprite(sprite), m_MaxVelocity(maxVelocity), m_Acceleration(acceleration), m_Deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::update(const float& dt)
{
	if (m_Velocity.x > 0.f)
	{
		m_Velocity.x -= m_Deceleration;
		if (m_Velocity.x < 0.f)
			m_Velocity.x = 0.f;
	}
	else if (m_Velocity.x < 0.f)
	{
		m_Velocity.x += m_Deceleration;
		if (m_Velocity.x > 0.f)
			m_Velocity.x = 0.f;
	}

	m_Sprite.move(m_Velocity * dt);
}

void MovementComponent::move(const float x, const float y, const float& dt)
{
	m_Velocity.x += m_Acceleration * x;

	if (m_Velocity.x > 0.f)
	{
		if (m_Velocity.x > m_MaxVelocity)
			m_Velocity.x = m_MaxVelocity;
	}
	else if (m_Velocity.x < 0.f)
	{
		if (m_Velocity.x < -m_MaxVelocity)
			m_Velocity.x = -m_MaxVelocity;
	}

	m_Velocity.y += m_Acceleration * y;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return m_Velocity;
}
