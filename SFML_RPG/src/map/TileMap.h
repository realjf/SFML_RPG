#pragma once

#include "tile/Tile.h"
#include "entities/Entity.h"

class Tile;
class Entity;

class TileMap
{
public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string textureFile);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	const sf::Texture* getTileSheet() const;

	void saveToFile(const std::string filename);
	void loadFromFile(const std::string filename);
	void clear();
	void updateCollision(Entity* entity, const float& dt);

private:
	std::vector<std::vector<std::vector<Tile*>>> m_Map;
	sf::Vector2u m_MaxSizeWorldGrid;
	unsigned m_GridSizeU;
	unsigned m_Layers;
	float m_GridSizeF;
	sf::Texture m_TileSheet;
	std::string m_TextureFile;
	sf::RectangleShape m_CollisionBox;
	sf::Vector2f m_MaxSizeWorldF;

	int m_FromX;
	int m_ToX;
	int m_FromY;
	int m_ToY;
	int m_Layer;
};

