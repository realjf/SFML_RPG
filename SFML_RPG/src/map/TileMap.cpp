#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, int width, int height, std::string textureFile)
{
	m_GridSizeF = gridSize;
	m_GridSizeI = static_cast<int>(m_GridSizeF);
	m_MaxSizeWorldGrid.x = width;
	m_MaxSizeWorldGrid.y = height;
	m_Layers = 1;
	m_TextureFile = textureFile;
	m_MaxSizeWorldF.x = static_cast<float>(width) * gridSize;
	m_MaxSizeWorldF.y = static_cast<float>(height) * gridSize;

	m_FromX = 0;
	m_FromY = 0;
	m_ToX = 0;
	m_ToY = 0;
	m_Layer = 0;
	
	m_Map.resize(m_MaxSizeWorldGrid.x, std::vector<std::vector<Tile*>>());
	for (int x = 0; x < m_MaxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < m_MaxSizeWorldGrid.y; y++)
		{
			m_Map[x].resize(m_MaxSizeWorldGrid.y, std::vector<Tile*>());

			for (int z = 0; z < m_Layers; z++)
			{
				m_Map[x][y].resize(m_Layers, NULL);
			}
		}
	}

	if (!m_TileSheet.loadFromFile(textureFile))
		std::cout << "ERROR:TILEMAP::FAILED to load tiletextureSheet." << std::endl;

	m_CollisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	m_CollisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	m_CollisionBox.setOutlineColor(sf::Color::Red);
	m_CollisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	clear();
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	if (entity)
	{
		m_Layer = 0;

		m_FromX = entity->getGridPosition(m_GridSizeI).x - 5;
		if (m_FromX < 0)
			m_FromX = 0;
		else if (m_FromX > m_MaxSizeWorldGrid.x)
			m_FromX = m_MaxSizeWorldGrid.x;

		m_ToX = entity->getGridPosition(m_GridSizeI).x + 8;
		if (m_ToX < 0)
			m_ToX = 0;
		else if (m_ToX > m_MaxSizeWorldGrid.x)
			m_ToX = m_MaxSizeWorldGrid.x;

		m_FromY = entity->getGridPosition(m_GridSizeI).y - 5;
		if (m_FromY < 0)
			m_FromY = 0;
		else if (m_FromY > m_MaxSizeWorldGrid.y)
			m_FromY = m_MaxSizeWorldGrid.y;

		m_ToY = entity->getGridPosition(m_GridSizeI).y + 8;
		if (m_ToY < 0)
			m_ToY = 0;
		else if (m_ToY > m_MaxSizeWorldGrid.y)
			m_ToY = m_MaxSizeWorldGrid.y;

		for (int x = m_FromX; x < m_ToX; x++)
		{
			for (int y = m_FromY; y < m_ToY; y++)
			{
				m_Map[x][y][m_Layer]->render(target);
				if (m_Map[x][y][m_Layer]->getCollision())
				{
					m_CollisionBox.setPosition(m_Map[x][y][m_Layer]->getPosition());
					target.draw(m_CollisionBox);
				}
			}
		}
	}
	else {
		for (auto& x : m_Map)
		{
			for (auto& y : x)
			{
				for (auto* z : y)
				{
					if (z != NULL)
					{
						z->render(target);
						if (z->getCollision())
						{
							m_CollisionBox.setPosition(z->getPosition());
							target.draw(m_CollisionBox);
						}
					}
				}
			}
		}
	}
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type)
{
	if (x < m_MaxSizeWorldGrid.x && x >= 0 && y < m_MaxSizeWorldGrid.y && y >= 0 && z < m_Layers && z >= 0)
	{
		if (m_Map[x][y][z] == NULL)
		{
			m_Map[x][y][z] = new Tile(x, y, m_GridSizeF, m_TileSheet, textureRect, collision, type);
		}
	}

}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if (x < m_MaxSizeWorldGrid.x && x >= 0 && y < m_MaxSizeWorldGrid.y && y >= 0 && z < m_Layers && z >= 0)
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
		outFile << m_MaxSizeWorldGrid.x << " " << m_MaxSizeWorldGrid.y << "\n"
			<< m_GridSizeI << "\n"
			<< m_Layers << "\n"
			<< m_TextureFile << "\n";

		for (int x = 0; x < m_MaxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < m_MaxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < m_Layers; z++)
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
		int gridSize = 0;
		int layers = 0;
		std::string textureFile = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		// basic
		inFile >> size.x >> size.y >> gridSize >> layers >> textureFile;

		m_GridSizeF = static_cast<float>(gridSize);
		m_GridSizeI = gridSize;
		m_MaxSizeWorldGrid.x = size.x;
		m_MaxSizeWorldGrid.y = size.y;
		m_Layers = layers;
		m_TextureFile = textureFile;

		clear();

		m_Map.resize(m_MaxSizeWorldGrid.x, std::vector<std::vector<Tile*>>());
		for (int x = 0; x < m_MaxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < m_MaxSizeWorldGrid.y; y++)
			{
				m_Map[x].resize(m_MaxSizeWorldGrid.y, std::vector<Tile*>());

				for (int z = 0; z < m_Layers; z++)
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
			m_Map[x][y][z] = new Tile(x, y , m_GridSizeF, m_TileSheet, sf::IntRect(trX, trY, m_GridSizeI, m_GridSizeI), collision, type);
		}
	}
	else {
		std::cout << "ERROR::TILEMAP::Could not load from file" << std::endl;
	}

	inFile.close();
}

void TileMap::clear()
{
	for (int x = 0; x < m_MaxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < m_MaxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < m_Layers; z++)
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

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	// world bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > m_MaxSizeWorldF.x)
	{
		entity->setPosition(m_MaxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > m_MaxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, m_MaxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	// tiles
	m_Layer = 0;
	m_FromX = entity->getGridPosition(m_GridSizeI).x - 5;
	if (m_FromX < 0)
		m_FromX = 0;
	else if (m_FromX > m_MaxSizeWorldGrid.x)
		m_FromX = m_MaxSizeWorldGrid.x;

	m_ToX = entity->getGridPosition(m_GridSizeI).x + 8;
	if (m_ToX < 0)
		m_ToX = 0;
	else if (m_ToX > m_MaxSizeWorldGrid.x)
		m_ToX = m_MaxSizeWorldGrid.x;

	m_FromY = entity->getGridPosition(m_GridSizeI).y - 5;
	if (m_FromY < 0)
		m_FromY = 0;
	else if (m_FromY > m_MaxSizeWorldGrid.y)
		m_FromY = m_MaxSizeWorldGrid.y;

	m_ToY = entity->getGridPosition(m_GridSizeI).y + 8;
	if (m_ToY < 0)
		m_ToY = 0;
	else if (m_ToY > m_MaxSizeWorldGrid.y)
		m_ToY = m_MaxSizeWorldGrid.y;


	for (int x = m_FromX; x < m_ToX; x++)
	{
		for (int y = m_FromY; y < m_ToY; y++)
		{
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = m_Map[x][y][m_Layer]->getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
			
			if (m_Map[x][y][m_Layer]->getCollision() && 
				m_Map[x][y][m_Layer]->intersects(nextPositionBounds))
			{
				//Bottom collision
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}

				//Top collision
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}

				//Right collision
				if (playerBounds.left < wallBounds.left
					&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}

				//Left collision
				else if (playerBounds.left > wallBounds.left
					&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}
			}
			
		}
	}

}
