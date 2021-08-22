#pragma once

#include "State.h"
#include "resources/Gui.h"

class SettingsState
	: public State
{
public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

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
	void initButtons();
};

