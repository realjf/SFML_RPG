#pragma once

#include "entities/Player.h"
#include "resources/GraphicsSettings.h"


class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {}

	float m_GridSize;
	sf::RenderWindow* m_Window;
	std::map<std::string, int>* m_SupportedKeys;
	std::stack<State*>* m_States;
	GraphicsSettings* m_GfxSettings;
};

class State
{
public:
	State(StateData* stateData);
	virtual ~State();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

	const bool& getQuit() const;
	virtual void updateInput(const float& dt) = 0;
	void endState();
	virtual void updateMousePositions(sf::View* view = NULL);
	void pauseState();
	void unpauseState();
	virtual void updateKeytime(const float& dt);
	const bool getKeytime();

protected:
	StateData* m_StateData;
	std::stack<State*>* m_States;
	sf::RenderWindow* m_Window;
	
	bool m_Quit;
	bool m_Paused;
	float m_Keytime;
	float m_KeytimeMax;
	float m_GridSize;
	std::map<std::string, int>* m_SupportedKeys;
	std::map<std::string, int> m_Keybinds;

	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;
	sf::Vector2u m_MousePosGrid;

	// resources
	std::map<std::string, sf::Texture> m_Textures;

	virtual void initKeybinds() = 0;

private:

};

