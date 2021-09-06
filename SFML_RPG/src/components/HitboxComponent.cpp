#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetx, float offsety, float width, float height)
	: m_Sprite(sprite), m_Offsetx(offsetx), m_Offsety(offsety)
{
	m_Hitbox.setPosition(m_Sprite.getPosition().x + offsetx, m_Sprite.getPosition().y + offsety);
	m_Hitbox.setSize(sf::Vector2f(width, height));
	m_Hitbox.setFillColor(sf::Color::Transparent);
	m_Hitbox.setOutlineThickness(-1.f);
	m_Hitbox.setOutlineColor(sf::Color::Green);
	m_NextPosition.left = 0.f;
	m_NextPosition.top = 0.f;
	m_NextPosition.width = width;
	m_NextPosition.height = height;
}

HitboxComponent::~HitboxComponent()
{

}

void HitboxComponent::update()
{
	m_Hitbox.setPosition(m_Sprite.getPosition().x + m_Offsetx, m_Sprite.getPosition().y + m_Offsety);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(m_Hitbox);
}

bool HitboxComponent::intersects(const sf::FloatRect& frect)
{
	return m_Hitbox.getGlobalBounds().intersects(frect);
}

const sf::Vector2f& HitboxComponent::getPosition() const
{
	return m_Hitbox.getPosition();
}

void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	m_Hitbox.setPosition(position);
	m_Sprite.setPosition(position.x - m_Offsetx, position.y - m_Offsety);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	m_Hitbox.setPosition(x, y);
	m_Sprite.setPosition(x - m_Offsetx, y - m_Offsety);
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return m_Hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	m_NextPosition.left = m_Hitbox.getPosition().x + velocity.x;
	m_NextPosition.top = m_Hitbox.getPosition().y + velocity.y;

	return m_NextPosition;
}
