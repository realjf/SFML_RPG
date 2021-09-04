#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect)
{
	m_Shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	m_Shape.setFillColor(sf::Color::White);
	/*m_Shape.setOutlineThickness(1.f);
	m_Shape.setOutlineColor(sf::Color::Black);*/
	m_Shape.setPosition(x, y);
	m_Shape.setTexture(&texture);
	m_Shape.setTextureRect(textureRect);
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
