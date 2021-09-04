#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	m_GridSizeF = gridSize;
	m_GridSizeU = static_cast<unsigned>(m_GridSizeF);
	m_MaxSize.x = width;
	m_MaxSize.y = height;
	m_Layers = 1;
	
	m_Map.resize(m_MaxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < m_MaxSize.x; x++)
	{
		for (size_t y = 0; y < m_MaxSize.y; y++)
		{
			m_Map[x].resize(m_MaxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < m_Layers; z++)
			{
				m_Map[x][y].resize(m_Layers, NULL);
			}
		}
	}

	if (!m_TileSheet.loadFromFile("resources/images/tiles/tilesheet1.png"))
		std::cout << "ERROR:TILEMAP::FAILED to load tiletextureSheet." << std::endl;
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < m_MaxSize.x; x++)
	{
		for (size_t y = 0; y < m_MaxSize.y; y++)
		{
			for (size_t z = 0; z < m_Layers; z++)
			{
				delete m_Map[x][y][z];
			}
		}
	}

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
			for (auto *z : y)
			{
				if(z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect)
{
	if (x < m_MaxSize.x && x >= 0 && y < m_MaxSize.y && y >= 0 && z < m_Layers && z >= 0)
	{
		if (m_Map[x][y][z] == NULL)
		{
			m_Map[x][y][z] = new Tile(x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF, m_TileSheet, textureRect);
		}
	}

}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < m_MaxSize.x && x >= 0 && y < m_MaxSize.y && y >= 0 && z < m_Layers && z >= 0)
	{
		if (m_Map[x][y][z] != NULL)
		{
			delete m_Map[x][y][z];
			m_Map[x][y][z] = NULL;
		}
	}
}

sf::Texture* TileMap::getTileSheet()
{
	return &m_TileSheet;
}
