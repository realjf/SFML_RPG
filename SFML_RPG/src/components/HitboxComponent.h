#pragma once



class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite& sprite, float offsetx, float offsety, float width, float height);
	virtual ~HitboxComponent();


	void update();
	void render(sf::RenderTarget& target);

	bool checkIntersect(const sf::FloatRect& frect);
private:
	sf::RectangleShape m_Hitbox;
	sf::Sprite& m_Sprite;
	float m_Offsetx;
	float m_Offsety;
};

