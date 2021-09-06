#include "stdafx.h"
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
		if (m_Velocity.x > m_MaxVelocity)
			m_Velocity.x = m_MaxVelocity;

		m_Velocity.x -= m_Deceleration;
		if (m_Velocity.x < 0.f)
			m_Velocity.x = 0.f;
	}
	else if (m_Velocity.x < 0.f)
	{
		if (m_Velocity.x < -m_MaxVelocity)
			m_Velocity.x = -m_MaxVelocity;

		m_Velocity.x += m_Deceleration;
		if (m_Velocity.x > 0.f)
			m_Velocity.x = 0.f;
	}
	if (m_Velocity.y > 0.f)
	{
		if (m_Velocity.y > m_MaxVelocity)
			m_Velocity.y = m_MaxVelocity;

		m_Velocity.y -= m_Deceleration;
		if (m_Velocity.y < 0.f)
			m_Velocity.y = 0.f;
	}
	else if (m_Velocity.y < 0.f)
	{
		if (m_Velocity.y < -m_MaxVelocity)
			m_Velocity.y = -m_MaxVelocity;

		m_Velocity.y += m_Deceleration;
		if (m_Velocity.y > 0.f)
			m_Velocity.y = 0.f;
	}

	m_Sprite.move(m_Velocity * dt);
}

void MovementComponent::move(const float x, const float y, const float& dt)
{
	m_Velocity.x += m_Acceleration * x;
	m_Velocity.y += m_Acceleration * y;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return m_Velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return m_MaxVelocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (m_Velocity.x == 0.f && m_Velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (m_Velocity.x != 0.f && m_Velocity.y != 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (m_Velocity.x < 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (m_Velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (m_Velocity.y < 0.f)
			return true;
		break;
	case MOVING_DONW:
		if (m_Velocity.y > 0.f)
			return true;
		break;
	default:
		break;
	}
	return false;
}

void MovementComponent::stopVelocity()
{
	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	m_Velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	m_Velocity.y = 0.f;
}
