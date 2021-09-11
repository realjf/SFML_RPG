#pragma once

#include "State.h"
#include "gui/PauseMenu.h"
#include "map/TileMap.h"
#include "gui/PlayerGUI.h"

class PauseMenu;
class Player;
class PlayerGUI;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

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
	void updateView(const float& dt);
	void updateTileMap(const float& dt);
	void updatePlayerGUI(const float& dt);

private:
	Player* m_Player;
	PlayerGUI* m_PlayerGUI;
	PauseMenu* m_Pmenu;
	sf::Font m_Font;
	TileMap* m_TileMap;
	sf::View m_View;
	sf::RenderTexture m_RenderTexture;
	sf::Sprite m_RenderSprite;

	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
	void initTileMap();
	void initPlayerGUI();
};
