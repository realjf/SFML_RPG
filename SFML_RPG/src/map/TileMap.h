#pragma once

#include "tile/Tile.h"

class TileMap
{
public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string textureFile);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	const sf::Texture* getTileSheet() const;

	void saveToFile(const std::string filename);
	void loadFromFile(const std::string filename);
	void clear();

private:
	std::vector<std::vector<std::vector<Tile*>>> m_Map;
	sf::Vector2u m_MaxSize;
	unsigned m_GridSizeU;
	unsigned m_Layers;
	float m_GridSizeF;
	sf::Texture m_TileSheet;
	std::string m_TextureFile;
};

