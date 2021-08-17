#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
	initPlayers();
}

GameState::~GameState()
{
	delete m_Player;
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	
	m_Player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;
	m_Player->render(*target);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		m_Player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		m_Player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		m_Player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		m_Player->move(0.f, 1.f, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
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

