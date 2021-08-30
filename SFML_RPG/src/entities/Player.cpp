#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, sf::Texture& textureSheet)
{
	initVariables();

	setPosition(x, y);

	createHitboxComponent(m_Sprite, 86.f, 66.f, 86.f, 114.f);
	createMovementComponent(350.f, 15.f, 5.f);
	createAnimationComponent(textureSheet);

	m_AnimationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
	m_AnimationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
	m_AnimationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	m_MovementComponent->update(dt);

	updateAttack();
	updateAnimation(dt);

	m_HitboxComponent->update();
}

void Player::updateAnimation(const float& dt)
{
	if (m_Attacking)
	{
		if (m_Sprite.getScale().x > 0.f)
		{
			m_Sprite.setOrigin(96.f, 0.f);
		}
		else
		{
			m_Sprite.setOrigin(258.f + 96.f, 0.f);
		}

		if (m_AnimationComponent->play("ATTACK", dt, true))
		{
			m_Attacking = false;

			if (m_Sprite.getScale().x > 0.f)
			{
				m_Sprite.setOrigin(0.f, 0.f);
			}
			else
			{
				m_Sprite.setOrigin(258.f, 0.f);
			}
		}
	}

	if (m_MovementComponent->getState(IDLE))
		m_AnimationComponent->play("IDLE", dt);
	else if (m_MovementComponent->getState(MOVING_LEFT))
	{
		if (m_Sprite.getScale().x < 0.f)
		{
			m_Sprite.setOrigin(0.f, 0.f);
			m_Sprite.setScale(1.f, 1.f);
		}
		m_AnimationComponent->play("WALK", dt, m_MovementComponent->getVelocity().x, m_MovementComponent->getMaxVelocity());
	}
	else if (m_MovementComponent->getState(MOVING_RIGHT))
	{
		if (m_Sprite.getScale().x > 0.f)
		{
			m_Sprite.setOrigin(258.f, 0.f);
			m_Sprite.setScale(-1.f, 1.f);
		}
		m_AnimationComponent->play("WALK", dt, m_MovementComponent->getVelocity().x, m_MovementComponent->getMaxVelocity());
	}
	else if (m_MovementComponent->getState(MOVING_UP))
	{
		m_AnimationComponent->play("WALK", dt, m_MovementComponent->getVelocity().y, m_MovementComponent->getMaxVelocity());
	}
	else if (m_MovementComponent->getState(MOVING_DONW))
	{
		m_AnimationComponent->play("WALK", dt, m_MovementComponent->getVelocity().y, m_MovementComponent->getMaxVelocity());
	}
	
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_Attacking = true;
	}
}

void Player::initVariables()
{
	m_Attacking = false;
}

void Player::initComponents()
{
	
}
