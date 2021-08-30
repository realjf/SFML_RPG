#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF)
{
	m_Shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	m_Shape.setFillColor(sf::Color::Green);
	m_Shape.setPosition(x, y);
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
