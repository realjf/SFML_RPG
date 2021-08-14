#pragma once

#include "State.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
	void updateKeybinds(const float& dt);
	void endState();
};
