#pragma once

#include "states/GameState.h"
#include "states/MainMenuState.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
	void endApplication();

private:
	sf::RenderWindow *m_Window;
	sf::Event m_SfEvent;
	std::vector<sf::VideoMode> m_VideoModes;
	sf::ContextSettings m_WindowSettings;
	bool m_Fullscreen;

	sf::Clock m_DtClock;
	float m_Dt;

	std::stack<State*> m_States;
	std::map<std::string, int> m_SupportedKeys;

	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();

};

