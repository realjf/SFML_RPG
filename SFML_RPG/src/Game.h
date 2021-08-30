#pragma once

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
	
	GraphicsSettings m_GfxSettings;
	sf::RenderWindow *m_Window;
	sf::Event m_SfEvent;

	sf::Clock m_DtClock;
	float m_Dt;

	std::stack<State*> m_States;
	std::map<std::string, int> m_SupportedKeys;

	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStates();
	void initKeys();

};

