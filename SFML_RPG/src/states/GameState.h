#pragma once

#include "State.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updateInput(const float& dt);

private:
	Player* m_Player;

	void initKeybinds();
	void initTextures();
	void initPlayers();
};
