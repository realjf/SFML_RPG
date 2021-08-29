#include "TileMap.h"

TileMap::TileMap()
{
	m_GridSizeU = 50;
	m_MaxSize.x = 5000;
	m_MaxSize.y = 5000;
	m_Layers = 5;
	
	for (size_t x = 0; x < m_MaxSize.x; x++)
	{
		m_Map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y = 0; y < m_MaxSize.y; y++)
		{
			m_Map[x].push_back(std::vector<Tile>());

			for (size_t z = 0; z < m_Layers; z++)
			{
				m_Map[x][y].push_back(Tile());
			}
		}
	}
}

TileMap::~TileMap()
{

}
