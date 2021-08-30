#pragma once

#include "GameState.h"
#include "resources/Gui.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "resources/GraphicsSettings.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget& target);

private:
	sf::Texture m_BackgroundTexture;
	sf::RectangleShape m_Background;
	sf::Font m_Font;
	GraphicsSettings& m_GfxSettings;

	std::map<std::string, GUI::Button*> m_Buttons;

	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initButtons();
};

