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
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class State
{
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void checkForQuit();
	const bool& getQuit() const;
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void endState() = 0;

private:
	std::vector<sf::Texture> m_Textures;
	sf::RenderWindow* m_Window;
	bool m_Quit;
};

