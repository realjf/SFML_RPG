#include "stdafx.h"
#include "State.h"


State::State(StateData* stateData)
{
	m_StateData = stateData;
	m_Window = stateData->m_Window;
	m_Quit = false;
	m_Paused = false;
	m_SupportedKeys = stateData->m_SupportedKeys;
	m_States = stateData->m_States;
	m_Keytime = 0.f;
	m_KeytimeMax = 50.f;
	m_GridSize = stateData->m_GridSize;
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

void State::updateMousePositions(sf::View* view)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(*m_Window);

	if(view)
		m_Window->setView(*view);

	m_MousePosView = m_Window->mapPixelToCoords(sf::Mouse::getPosition(*m_Window));
	m_MousePosGrid = sf::Vector2i(
		static_cast<int>(m_MousePosView.x) / static_cast<int>(m_GridSize),
		static_cast<int>(m_MousePosView.y) / static_cast<int>(m_GridSize)
	);

	m_Window->setView(m_Window->getDefaultView());
}

void State::pauseState()
{
	m_Paused = true;
}

void State::unpauseState()
{
	m_Paused = false;
}

void State::updateKeytime(const float& dt)
{
	if (m_Keytime < m_KeytimeMax)
		m_Keytime += 100.f * dt;
}

const bool State::getKeytime()
{
	if (m_Keytime >= m_KeytimeMax)
	{
		m_Keytime = 0.f;
		return true;
	}
	return false;
}


