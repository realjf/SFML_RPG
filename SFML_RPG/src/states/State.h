#pragma once

#include "entities/Player.h"

class State
{
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

	const bool& getQuit() const;
	virtual void updateInput(const float& dt) = 0;
	void endState();
	virtual void updateMousePositions();
	void pauseState();
	void unpauseState();

protected:
	std::stack<State*>* m_States;
	sf::RenderWindow* m_Window;
	bool m_Quit;
	bool m_Paused;
	std::map<std::string, int>* m_SupportedKeys;
	std::map<std::string, int> keybinds;

	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;

	// resources
	std::map<std::string, sf::Texture> m_Textures;

	virtual void initKeybinds() = 0;

private:

};

