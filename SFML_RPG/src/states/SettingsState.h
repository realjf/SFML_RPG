#pragma once

#include "State.h"
#include "gui/Gui.h"

class SettingsState
	: public State
{
public:
	SettingsState(StateData* stateData);
	virtual ~SettingsState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void renderGui(sf::RenderTarget& target);

private:
	sf::Texture m_BackgroundTexture;
	sf::RectangleShape m_Background;
	sf::Font m_Font;

	std::map<std::string, GUI::Button*> m_Buttons;
	std::map<std::string, GUI::DropDownList*> m_DropDownLists;

	sf::Text m_OptionsText;
	std::vector<sf::VideoMode> m_Modes;

	void initVariables();
	void initKeybinds();
	void initFonts();
	void initGui();
	void resetGui();
};

