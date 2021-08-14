#pragma once

#include "states/GameState.h"

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

	sf::Clock m_DtClock;
	float m_Dt;

	std::stack<State*> m_States;

	void initWindow();
	void initStates();

};

