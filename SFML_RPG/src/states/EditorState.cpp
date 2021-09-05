#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* stateData)
	: State(stateData)
{
	initVariables();
	initBackground();
	initFonts();
	initText();
	initKeybinds();
	initPauseMenu();
	initButtons();
	initTileMap();
	initGui();
}

EditorState::~EditorState()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
	delete m_Pmenu;
	delete m_TileMap;
	delete m_TextureSelector;
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateKeytime(dt);
	updateInput(dt);

	if (!m_Paused)
	{
		updateButtons();
		updateGui(dt);
		updateEditorInput(dt);
	}
	else {
		m_Pmenu->update(m_MousePosView);
		updatePauseMenuButtons();
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;

	m_TileMap->render(*target);

	renderButtons(*target);
	renderGui(*target);

	if (m_Paused)
	{
		m_Pmenu->render(*target);
	}
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("CLOSE"))) && getKeytime())
	{
		if (!m_Paused)
			pauseState();
		else
			unpauseState();
	}
}


void EditorState::updateButtons()
{
	for (auto& it : m_Buttons)
	{
		it.second->update(m_MousePosView);
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : m_Buttons)
	{
		it.second->render(target);
	}
}

void EditorState::updatePauseMenuButtons()
{
	if (m_Pmenu->isButtonPressed("QUIT"))
		endState();

	if (m_Pmenu->isButtonPressed("SAVE"))
		m_TileMap->saveToFile("Text.slmp");

	if (m_Pmenu->isButtonPressed("LOAD"))
		m_TileMap->loadFromFile("Text.slmp");
}

void EditorState::updateGui(const float& dt)
{
	m_TextureSelector->update(m_MousePosWindow, dt);

	if (!m_TextureSelector->getActive())
	{
		m_SelectorRect.setTextureRect(m_TextureRect);
		m_SelectorRect.setPosition(m_MousePosGrid.x * m_StateData->m_GridSize, m_MousePosGrid.y * m_StateData->m_GridSize);
	}

	m_CursorText.setPosition(m_MousePosView.x + 100.f, m_MousePosView.y - 50.f);
	std::stringstream ss;
	ss << m_MousePosView.x << " " << m_MousePosView.y << std::endl 
		<< m_MousePosGrid.x << " " << m_MousePosGrid.y << std::endl
		<< m_TextureRect.left << " " << m_TextureRect.top;
	m_CursorText.setString(ss.str());
	
	
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	if(!m_TextureSelector->getActive())
		target.draw(m_SelectorRect);
	
	m_TextureSelector->render(target);
	target.draw(m_CursorText);
	target.draw(m_Sidebar);
}

void EditorState::updateEditorInput(const float& dt)
{
	// add a tile to the tileMap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeytime())
	{
		if (!m_Sidebar.getGlobalBounds().contains(sf::Vector2f(m_MousePosWindow)))
		{
			if (!m_TextureSelector->getActive())
			{
				m_TileMap->addTile(m_MousePosGrid.x, m_MousePosGrid.y, 0, m_TextureRect);
			}
			else
			{
				m_TextureRect = m_TextureSelector->getTextureRect();
			}
		}
	}
	else  if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeytime())
	{
		if (!m_Sidebar.getGlobalBounds().contains(sf::Vector2f(m_MousePosWindow)))
		{
			if (!m_TextureSelector->getActive())
				m_TileMap->removeTile(m_MousePosGrid.x, m_MousePosGrid.y, 0);
		}
		
	}
}

void EditorState::initVariables()
{
	m_TextureRect = sf::IntRect(0, 0, static_cast<int>(m_StateData->m_GridSize), static_cast<int>(m_StateData->m_GridSize));
}

void EditorState::initBackground()
{
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("config/editorstate_keybinds.ini");

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

void EditorState::initFonts()
{
	if (!m_Font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		throw("Error::MainMenuState::Could_not_load_font");
	}
}

void EditorState::initButtons()
{
	
}

void EditorState::initPauseMenu()
{
	m_Pmenu = new PauseMenu(*m_Window, m_Font);
	m_Pmenu->addButton("QUIT", 800.f, "Quit");
	m_Pmenu->addButton("SAVE", 500.f, "Save");
	m_Pmenu->addButton("LOAD", 400.f, "Load");
}

void EditorState::initGui()
{
	m_Sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.height)));
	m_Sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	m_Sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	m_Sidebar.setOutlineThickness(1.f);

	m_SelectorRect.setSize(sf::Vector2f(m_StateData->m_GridSize, m_StateData->m_GridSize));
	m_SelectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	
	m_SelectorRect.setOutlineThickness(1.f);
	m_SelectorRect.setOutlineColor(sf::Color::Green);

	m_SelectorRect.setTexture(m_TileMap->getTileSheet());
	m_SelectorRect.setTextureRect(m_TextureRect);

	m_TextureSelector = new GUI::TextureSelector(20.f, 20.f, 800.f, 400.f, m_StateData->m_GridSize, m_TileMap->getTileSheet(),
		m_Font, "TS");
}

void EditorState::initTileMap()
{
	m_TileMap = new TileMap(m_StateData->m_GridSize, 10, 10, "resources/images/tiles/tilesheet1.png");
}

void EditorState::initText()
{
	m_CursorText.setFont(m_Font);
	m_CursorText.setFillColor(sf::Color::White);
	m_CursorText.setCharacterSize(12);
	m_CursorText.setPosition(m_MousePosView.x, m_MousePosView.y);
}
