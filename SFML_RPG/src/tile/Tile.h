#pragma once


enum TileTypes { DEFAULT = 0, DAMAGING };

class Tile
{
public:
	Tile();
	Tile(unsigned gridx, unsigned gridy, float gridSizeF, sf::Texture& texture, const sf::IntRect& textureRect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);

	const std::string getAsString() const;
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const sf::FloatRect getGlobalBounds() const;

private:

protected:
	sf::RectangleShape m_Shape;
	short m_Type;
	bool m_Collision;

};

