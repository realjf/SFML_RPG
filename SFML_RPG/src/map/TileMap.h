#pragma once

#include "tile/Tile.h"

class TileMap
{
public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);

	void addTile();
	void removeTile();

private:
	std::vector<std::vector<std::vector<Tile>>> m_Map;
	sf::Vector2u m_MaxSize;
	unsigned m_GridSizeU;
	unsigned m_Layers;
	float m_GridSizeF;
};

