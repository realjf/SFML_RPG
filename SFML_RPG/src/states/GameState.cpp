#include "stdafx.h"
#include "GameState.h"

GameState::GameState(StateData* stateData)
	: State(stateData)
{
	initDeferredRender();
	initView();
	initKeybinds();
	initFonts();
	initTextures();
	initPauseMenu();
	initPlayers();
	initTileMap();
}

GameState::~GameState()
{
	delete m_Player;
	delete m_Pmenu;
	delete m_TileMap;
}

void GameState::update(const float& dt)
{
	updateMousePositions(&m_View);
	updateKeytime(dt);
	updateInput(dt);
	

	if (!m_Paused) 
	{	
		updateView(dt);
		updatePlayerInput(dt);

		updateTileMap(dt);
		m_Player->update(dt);
		
	}
	else { // paused update

		m_Pmenu->update(m_MousePosWindow);
		updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;

	m_RenderTexture.clear();

	m_RenderTexture.setView(m_View);
	m_TileMap->render(m_RenderTexture, m_Player->getGridPosition(static_cast<int>(m_StateData->m_GridSize)));

	m_Player->render(m_RenderTexture);

	m_TileMap->renderDeferred(m_RenderTexture);

	if (m_Paused)
	{
		m_RenderTexture.setView(m_RenderTexture.getDefaultView());
		m_Pmenu->render(m_RenderTexture);
	}

	// final render
	m_RenderTexture.display();
	//m_RenderSprite.setTexture(m_RenderTexture.getTexture());
	target->draw(m_RenderSprite);

}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_LEFT"))))
		m_Player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_RIGHT"))))
		m_Player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_UP"))))
		m_Player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_DOWN"))))
		m_Player->move(0.f, 1.f, dt);

}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("CLOSE"))) && getKeytime())
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

void GameState::updateView(const float& dt)
{
	m_View.setCenter(std::floor(m_Player->getPosition().x), std::floor(m_Player->getPosition().y));
}

void GameState::updateTileMap(const float& dt)
{
	m_TileMap->update();
	m_TileMap->updateCollision(m_Player, dt);
}

void GameState::initDeferredRender()
{
	m_RenderTexture.create(
		m_StateData->m_GfxSettings->m_Resolution.width,
		m_StateData->m_GfxSettings->m_Resolution.height
	);

	m_RenderSprite.setTexture(m_RenderTexture.getTexture());
	m_RenderSprite.setTextureRect(
		sf::IntRect(
			0, 
			0, 
			m_StateData->m_GfxSettings->m_Resolution.width,
			m_StateData->m_GfxSettings->m_Resolution.height
		)
	);
}

void GameState::initView()
{
	m_View.setSize(
		sf::Vector2f(
			static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.width),
			static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.height)
		)
	);
	m_View.setCenter(
		sf::Vector2f(
			static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.width) / 2.f,
			static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.height) / 2.f
		)
	);
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
			m_Keybinds[key] = m_SupportedKeys->at(key2);
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

void GameState::initTileMap()
{
	m_TileMap = new TileMap(m_StateData->m_GridSize, 1000, 1000, "resources/images/tiles/tilesheet1.png");
	m_TileMap->loadFromFile("Text.slmp");
}
