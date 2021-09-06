#pragma once



class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite& sprite, float offsetx, float offsety, float width, float height);
	virtual ~HitboxComponent();


	void update();
	void render(sf::RenderTarget& target);

	bool intersects(const sf::FloatRect& frect);
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

private:
	sf::RectangleShape m_Hitbox;
	sf::Sprite& m_Sprite;
	float m_Offsetx;
	float m_Offsety;
	sf::FloatRect m_NextPosition;
};

