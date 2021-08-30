#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	m_GridSizeF = 50.f;
	m_GridSizeU = static_cast<unsigned>(m_GridSizeF);
	m_MaxSize.x = 100;
	m_MaxSize.y = 100;
	m_Layers = 1;
	
	m_Map.resize(m_MaxSize.x);
	for (size_t x = 0; x < m_MaxSize.x; x++)
	{
		m_Map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y = 0; y < m_MaxSize.y; y++)
		{
			m_Map[x].resize(m_MaxSize.y);
			m_Map[x].push_back(std::vector<Tile>());

			for (size_t z = 0; z < m_Layers; z++)
			{
				m_Map[x][y].resize(m_Layers);
				m_Map[x][y].push_back(Tile(x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{

}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : m_Map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}
