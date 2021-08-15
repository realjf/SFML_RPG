#include "Game.h"

// static functions

// init functions

// constructor/destructor

Game::Game()
{
	initWindow();
	initKeys();
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
		m_States.top()->update(m_Dt);
		if (m_States.top()->getQuit())
		{
			m_States.top()->endState();
			delete m_States.top();
			m_States.pop();
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
	m_Fullscreen = false;
	m_Dt = 0.f;

}

void Game::initWindow()
{
	std::ifstream ifs("config/window.ini");
	m_VideoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	m_WindowSettings.antialiasingLevel = antialiasing_level;
	m_Fullscreen = fullscreen;
	if (m_Fullscreen)
		m_Window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, m_WindowSettings);
	else 
		m_Window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, m_WindowSettings);
	
	m_Window->setFramerateLimit(framerate_limit);
	m_Window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	m_States.push(new MainMenuState(m_Window, &m_SupportedKeys, &m_States));
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
