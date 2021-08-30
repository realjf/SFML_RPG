#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class Tile
{
public:
	Tile();
	Tile(float x, float y, float gridSizeF);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);

private:

protected:
	sf::RectangleShape m_Shape;


};

