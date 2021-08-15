#pragma once


#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class MovementComponent
{

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	void update(const float& dt);
	void move(const float x, const float y, const float& dt);

	const sf::Vector2f& getVelocity() const;
private:
	sf::Sprite& m_Sprite;

	float m_MaxVelocity;
	sf::Vector2f m_Velocity;
	float m_Acceleration;
	float m_Deceleration;


};

