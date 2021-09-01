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
	m_KeytimeMax = 100.f;
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

void State::updateMousePositions()
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(*m_Window);
	m_MousePosView = m_Window->mapPixelToCoords(sf::Mouse::getPosition(*m_Window));
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
