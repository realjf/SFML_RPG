#include "stdafx.h"
#include "Game.h"

// static functions

// init functions

// constructor/destructor

Game::Game()
{
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeys();
	initStateData();
	initStates();
}

Game::~Game()
{
	delete m_Window;
	while (!m_States.empty())
	{
		delete m_States.top();
		m_States.pop();
	}
}

void Game::updateDt()
{
	m_Dt = m_DtClock.restart().asSeconds();
	//system("cls");
	//std::cout << m_Dt << std::endl;
}

void Game::updateSFMLEvents()
{
	while (m_Window->pollEvent(m_SfEvent))
	{
		if (m_SfEvent.type == sf::Event::Closed)
			m_Window->close();
	}
}

void Game::update()
{
	updateSFMLEvents();

	if (!m_States.empty())
	{
		if (m_Window->hasFocus())
		{
			m_States.top()->update(m_Dt);
			if (m_States.top()->getQuit())
			{
				m_States.top()->endState();
				delete m_States.top();
				m_States.pop();
			}
		}
		
	}
	// APP END
	else
	{
		endApplication();
		m_Window->close();
	}

	
}

void Game::render()
{
	m_Window->clear();

	// render 
	if (!m_States.empty())
		m_States.top()->render();

	m_Window->display();
}

void Game::run()
{
	while (m_Window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

void Game::endApplication()
{
	std::cout << "ending application" << std::endl;
}

void Game::initVariables()
{
	m_Window = NULL;
	m_Dt = 0.f;

	m_GridSize = 100.f;

}

void Game::initGraphicsSettings()
{
	m_GfxSettings.loadFromFile("config/graphics.ini");
}

void Game::initWindow()
{
	if (m_GfxSettings.m_Fullscreen)
		m_Window = new sf::RenderWindow(m_GfxSettings.m_Resolution, m_GfxSettings.m_Title, sf::Style::Fullscreen, m_GfxSettings.m_ContextSettings);
	else 
		m_Window = new sf::RenderWindow(m_GfxSettings.m_Resolution, m_GfxSettings.m_Title, sf::Style::Titlebar | sf::Style::Close, m_GfxSettings.m_ContextSettings);
	
	m_Window->setFramerateLimit(m_GfxSettings.m_FrameRateLimit);
	m_Window->setVerticalSyncEnabled(m_GfxSettings.m_VerticalSync);
}

void Game::initStates()
{
	m_States.push(new MainMenuState(&m_StateData));
	//m_States.push(new GameState(m_Window, &m_SupportedKeys));
}

void Game::initKeys()
{
	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			m_SupportedKeys[key] = key_value;
		}
	}

	ifs.close();

	for (auto i : m_SupportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStateData()
{
	m_StateData.m_Window = m_Window;
	m_StateData.m_GfxSettings = &m_GfxSettings;
	m_StateData.m_SupportedKeys = &m_SupportedKeys;
	m_StateData.m_States = &m_States;
	m_StateData.m_GridSize = m_GridSize;
}
