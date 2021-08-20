#pragma once


#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "resources/Button.h"

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

	void update();
	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape m_Background;
	sf::RectangleShape m_Container;
	sf::Font& m_Font;
	sf::Text m_MenuText;

	std::map<std::string, Button*> m_Buttons;
};

