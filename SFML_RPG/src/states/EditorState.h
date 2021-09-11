#pragma once

#include "State.h"
#include "gui/Gui.h"
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
	void updateGui(const float& dt);
	void renderGui(sf::RenderTarget& target);
	void updateEditorInput(const float& dt);

private:
	sf::View m_View;
	sf::Font m_Font;
	PauseMenu* m_Pmenu;
	TileMap* m_TileMap;

	std::map<std::string, GUI::Button*> m_Buttons;
	sf::RectangleShape m_SelectorRect;
	sf::IntRect m_TextureRect;
	sf::Text m_CursorText;
	GUI::TextureSelector* m_TextureSelector;
	sf::RectangleShape m_Sidebar;
	

	bool m_Collision;
	short m_Type;
	float m_CameraSpeed;
	int m_Layer;

	void initVariables();
	void initView();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initButtons();
	void initPauseMenu();
	void initGui();
	void initTileMap();
	void initText();
};

