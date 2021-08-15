#include "State.h"


State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	m_Window = window;
	m_Quit = false;
	m_SupportedKeys = supportedKeys;
	m_States = states;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return m_Quit;
}

void State::endState()
{
	m_Quit = true;
}

void State::updateMousePositions()
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(*m_Window);
	m_MousePosView = m_Window->mapPixelToCoords(sf::Mouse::getPosition(*m_Window));
}
