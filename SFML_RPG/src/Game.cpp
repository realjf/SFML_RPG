#include "Game.h"

// static functions

// init functions

// constructor/destructor

Game::Game()
{
	initWindow();
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

void Game::initWindow()
{
	std::ifstream ifs("config/window.ini");
	std::string title = "None";
	sf::VideoMode window_bounds(800, 600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	m_Window = new sf::RenderWindow(window_bounds, title);
	m_Window->setFramerateLimit(framerate_limit);
	m_Window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	m_States.push(new GameState(m_Window));
}
