#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string textureFile)
{
	m_GridSizeF = gridSize;
	m_GridSizeU = static_cast<unsigned>(m_GridSizeF);
	m_MaxSize.x = width;
	m_MaxSize.y = height;
	m_Layers = 1;
	m_TextureFile = textureFile;
	
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

	if (!m_TileSheet.loadFromFile(textureFile))
		std::cout << "ERROR:TILEMAP::FAILED to load tiletextureSheet." << std::endl;
}

TileMap::~TileMap()
{
	clear();
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
			m_Map[x][y][z] = new Tile(x, y, m_GridSizeF, m_TileSheet, textureRect);
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

const sf::Texture* TileMap::getTileSheet() const
{
	return &m_TileSheet;
}

void TileMap::saveToFile(const std::string filename)
{
	/**
	 * Format:
	 * Basic:
	 * Size x y
	 * gridSize
	 * layers
	 * texture file
	 * 
	 * all tiles:
	 * gridPos x y layer, texture rect x y,collision,type
	 */
	std::ofstream outFile;
	outFile.open(filename);
	if (outFile.is_open())
	{
		outFile << m_MaxSize.x << " " << m_MaxSize.y << "\n"
			<< m_GridSizeU << "\n"
			<< m_Layers << "\n"
			<< m_TextureFile << "\n";

		for (size_t x = 0; x < m_MaxSize.x; x++)
		{
			for (size_t y = 0; y < m_MaxSize.y; y++)
			{
				for (size_t z = 0; z < m_Layers; z++)
				{
					if(m_Map[x][y][z])
						outFile << x << " " << y << " " << z << " " << m_Map[x][y][z]->getAsString() << " ";
				}
			}
		}
	}
	else {
		std::cout << "ERROR::TILEMAP::Could not save to file " << std::endl;
	}

	outFile.close();
}

void TileMap::loadFromFile(const std::string filename)
{
	std::ifstream inFile;
	inFile.open(filename);
	if (inFile.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string textureFile = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		// basic
		inFile >> size.x >> size.y >> gridSize >> layers >> textureFile;

		m_GridSizeF = static_cast<float>(gridSize);
		m_GridSizeU = gridSize;
		m_MaxSize.x = size.x;
		m_MaxSize.y = size.y;
		m_Layers = layers;
		m_TextureFile = textureFile;

		clear();

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

		if (!m_TileSheet.loadFromFile(textureFile))
			std::cout << "ERROR:TILEMAP::FAILED to load tiletextureSheet." << std::endl;

		// load all tiles
		while (inFile >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			m_Map[x][y][z] = new Tile(x, y , m_GridSizeF, m_TileSheet, sf::IntRect(trX, trY, m_GridSizeU, m_GridSizeU), collision, type);
		}
	}
	else {
		std::cout << "ERROR::TILEMAP::Could not load from file" << std::endl;
	}

	inFile.close();
}

void TileMap::clear()
{
	for (size_t x = 0; x < m_MaxSize.x; x++)
	{
		for (size_t y = 0; y < m_MaxSize.y; y++)
		{
			for (size_t z = 0; z < m_Layers; z++)
			{
				delete m_Map[x][y][z];
				m_Map[x][y][z] = NULL;
			}
			m_Map[x][y].clear();
		}
		m_Map[x].clear();
	}

	m_Map.clear();

	// std::cout << m_Map.size() << std::endl;
}
