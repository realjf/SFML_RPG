#pragma once

#include "State.h"
#include "resources/Gui.h"
#include "gui/PauseMenu.h"
#include "map/TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;


class EditorState
	: public State
{
public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget& target);
	void updatePauseMenuButtons();
	void updateGui();
	void renderGui(sf::RenderTarget& target);

private:
	sf::Font m_Font;
	PauseMenu* m_Pmenu;
	TileMap* m_TileMap;

	std::map<std::string, GUI::Button*> m_Buttons;
	sf::RectangleShape m_SelectorRect;

	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initButtons();
	void initPauseMenu();
	void initGui();
	void initTileMap();
};

