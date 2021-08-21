#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initKeybinds();
	initFonts();
	initTextures();
	initPauseMenu();
	initPlayers();
}

GameState::~GameState()
{
	delete m_Player;
	delete m_Pmenu;
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateKeytime(dt);

	if (!m_Paused) 
	{	
		updatePlayerInput(dt);

		m_Player->update(dt);
	}
	else { // paused update

		m_Pmenu->update(m_MousePosView);
		updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;
	m_Player->render(*target);

	if (m_Paused)
	{
		m_Pmenu->render(*target);
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		m_Player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		m_Player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		m_Player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		m_Player->move(0.f, 1.f, dt);

}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
	{
		if (!m_Paused)
			pauseState();
		else
			unpauseState();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (m_Pmenu->isButtonPressed("QUIT"))
		endState();
}

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			keybinds[key] = m_SupportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initTextures()
{
	if (!m_Textures["PLAYER_SHEET"].loadFromFile("resources/images/sprites/player/PLAYER_SHEET.png"))
	{
		throw("Error::GameState::Could_not_load_player_texture");
	}
}

void GameState::initPlayers()
{
	m_Player = new Player(0, 0, m_Textures["PLAYER_SHEET"]);
}

void GameState::initFonts()
{
	if (!m_Font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		throw("Error::MainMenuState::Could_not_load_font");
	}
}

void GameState::initPauseMenu()
{
	m_Pmenu = new PauseMenu(*m_Window, m_Font);
	m_Pmenu->addButton("QUIT", 800.f, "Quit");
}
