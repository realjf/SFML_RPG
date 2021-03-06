#pragma once

#include "gui/Gui.h"

class Gui;

class PauseMenu
{
public:
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~PauseMenu();

	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);

	std::map<std::string, GUI::Button*>& getButtons();
	void addButton(const std::string key, const float y, const float width, const float height, const unsigned charSize, const std::string text);
	const bool isButtonPressed(const std::string key);


private:
	sf::RectangleShape m_Background;
	sf::RectangleShape m_Container;
	sf::Font& m_Font;
	sf::Text m_MenuText;

	std::map<std::string, GUI::Button*> m_Buttons;
};

