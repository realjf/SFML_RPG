#include "State.h"


State::State(sf::RenderWindow* window)
{
	m_Window = window;
	m_Quit = false;
}

State::~State()
{

}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_Quit = true;
	}
}

const bool& State::getQuit() const
{
	return m_Quit;
}
