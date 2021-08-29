#pragma once

#include "tile/Tile.h"

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();

private:
	std::vector<std::vector<std::vector<Tile>>> m_Map;
	sf::Vector2u m_MaxSize;
	unsigned m_GridSizeU;
	unsigned m_Layers;
};

