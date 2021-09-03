#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* stateData)
	: State(stateData)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initPauseMenu();
	initButtons();
	initGui();
	initTileMap();
}

EditorState::~EditorState()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
	delete m_Pmenu;
	delete m_TileMap;
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateKeytime(dt);
	updateInput(dt);

	if (!m_Paused)
	{
		updateButtons();
		updateGui();
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

	renderButtons(*target);
	renderGui(*target);

	m_TileMap->render(*target);

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
}

void EditorState::updateGui()
{
	m_SelectorRect.setPosition(m_MousePosView);
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(m_SelectorRect);
}

void EditorState::initVariables()
{

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
}

void EditorState::initGui()
{
	m_SelectorRect.setSize(sf::Vector2f(m_StateData->m_GridSize, m_StateData->m_GridSize));
	m_SelectorRect.setFillColor(sf::Color::Transparent);
	
	m_SelectorRect.setOutlineThickness(1.f);
	m_SelectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTileMap()
{
	m_TileMap = new TileMap(m_StateData->m_GridSize, 10, 10);
}
