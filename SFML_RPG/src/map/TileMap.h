#pragma once

#include "tile/Tile.h"
#include "entities/Entity.h"

class Tile;
class Entity;

class TileMap
{
public:
	TileMap(float gridSize, int width, int height, std::string textureFile);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);

	void addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);

	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;

	void saveToFile(const std::string filename);
	void loadFromFile(const std::string filename);
	void clear();
	void updateCollision(Entity* entity, const float& dt);
	void renderDeferred(sf::RenderTarget& target);

private:
	std::vector<std::vector<std::vector< std::vector<Tile*> >>> m_Map;
	sf::Vector2i m_MaxSizeWorldGrid;
	int m_GridSizeI;
	int m_Layers;
	float m_GridSizeF;
	sf::Texture m_TileSheet;
	std::string m_TextureFile;
	sf::RectangleShape m_CollisionBox;
	sf::Vector2f m_MaxSizeWorldF;
	std::stack<Tile*> m_DeferredRenderStack;

	int m_FromX;
	int m_ToX;
	int m_FromY;
	int m_ToY;
	int m_Layer;
};

