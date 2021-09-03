#pragma once

#include "State.h"
#include "gui/PauseMenu.h"
#include "map/TileMap.h"

class GameState : public State
{
public:
	GameState(StateData* stateData);
	virtual ~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
private:
	Player* m_Player;
	PauseMenu* m_Pmenu;
	sf::Font m_Font;
	TileMap* m_TileMap;

	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
	void initTileMap();
};
