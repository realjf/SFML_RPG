#pragma once

#include "GameState.h"
#include "resources/Button.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = NULL);

private:
	sf::Texture m_BackgroundTexture;
	sf::RectangleShape m_Background;
	sf::Font m_Font;

	std::map<std::string, Button*> m_Buttons;

	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initButtons();
};

