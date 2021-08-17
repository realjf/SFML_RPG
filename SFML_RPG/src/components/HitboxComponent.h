#pragma once



#include <iostream>
#include <ctime>
#include <cstdlib>


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

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

