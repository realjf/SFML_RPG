#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

class Button
{
public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f mousePos);

	const bool isPressed() const;
private:
	short unsigned m_ButtonState;

	sf::RectangleShape m_Shape;
	sf::Font* m_Font;
	sf::Text m_Text;

	sf::Color m_IdleColor;
	sf::Color m_HoverColor;
	sf::Color m_ActiveColor;



};

