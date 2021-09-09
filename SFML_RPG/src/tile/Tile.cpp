#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	m_Collision = false;
	m_Type = 0;
}

Tile::Tile(int gridx, int gridy, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect, bool collision, short type)
{
	m_Shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	m_Shape.setFillColor(sf::Color::White);
	/*m_Shape.setOutlineThickness(1.f);
	m_Shape.setOutlineColor(sf::Color::Black);*/
	m_Shape.setPosition(static_cast<float>(gridx) * gridSizeF, static_cast<float>(gridy) * gridSizeF);
	m_Shape.setTexture(&texture);
	m_Shape.setTextureRect(textureRect);

	m_Collision = collision;
	m_Type = type;
}

Tile::~Tile()
{

}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(m_Shape);
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << m_Shape.getTextureRect().left << " " << m_Shape.getTextureRect().top << " " << m_Collision << " " << m_Type;

	return ss.str();
}

const sf::Vector2f& Tile::getPosition() const
{
	return m_Shape.getPosition();
}

const bool& Tile::getCollision() const
{
	return m_Collision;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return m_Shape.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return m_Shape.getGlobalBounds();
}

const short& Tile::getType() const
{
	return m_Type;
}
