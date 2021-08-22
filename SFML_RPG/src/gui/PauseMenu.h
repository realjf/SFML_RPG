#pragma once


#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "resources/Gui.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

	std::map<std::string, GUI::Button*>& getButtons();
	void addButton(const std::string key, float y, const std::string text);
	const bool isButtonPressed(const std::string key);


private:
	sf::RectangleShape m_Background;
	sf::RectangleShape m_Container;
	sf::Font& m_Font;
	sf::Text m_MenuText;

	std::map<std::string, GUI::Button*> m_Buttons;
};

