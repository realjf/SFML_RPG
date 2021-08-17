#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetx, float offsety, float width, float height)
	: m_Sprite(sprite), m_Offsetx(offsetx), m_Offsety(offsety)
{
	m_Hitbox.setPosition(m_Sprite.getPosition().x + offsetx, m_Sprite.getPosition().y + offsety);
	m_Hitbox.setSize(sf::Vector2f(width, height));
	m_Hitbox.setFillColor(sf::Color::Transparent);
	m_Hitbox.setOutlineThickness(-1.f);
	m_Hitbox.setOutlineColor(sf::Color::Green);
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

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return m_Hitbox.getGlobalBounds().intersects(frect);
}
