#pragma once

#include "State.h"
#include "resources/Gui.h"

class EditorState
	: public State
{
public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EditorState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget& target);

private:
	sf::Font m_Font;

	std::map<std::string, GUI::Button*> m_Buttons;

	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();
	void initButtons();
};

