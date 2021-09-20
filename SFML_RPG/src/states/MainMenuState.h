#pragma once

#include "GameState.h"
#include "gui/Gui.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "resources/GraphicsSettings.h"

class MainMenuState : public State
{
public:
	MainMenuState(StateData* stateData);
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

	std::map<std::string, GUI::Button*> m_Buttons;

	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initGui();
	void resetGui();
};

