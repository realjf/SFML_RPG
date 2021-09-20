#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* stateData)
	: State(stateData)
{
	initVariables();
	initView();
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
	updateMousePositions(&m_View);
	updateKeytime(dt);
	updateInput(dt);

	if (!m_Paused)
	{
		updateButtons();
		updateGui(dt);
		updateEditorInput(dt);
	}
	else {
		m_Pmenu->update(m_MousePosWindow);
		updatePauseMenuButtons();
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;

	target->setView(m_View);
	m_TileMap->render(*target, m_MousePosGrid);
	m_TileMap->renderDeferred(*target);

	target->setView(m_Window->getDefaultView());

	renderButtons(*target);
	renderGui(*target);

	if (m_Paused)
	{
		target->setView(m_Window->getDefaultView());
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
		it.second->update(m_MousePosWindow);
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
		<< m_TextureRect.left << " " << m_TextureRect.top << std::endl
		<< "collision: " << m_Collision << std::endl
		<< "type: " << m_Type << std::endl
		<< "tiles: " << m_TileMap->getLayerSize(m_MousePosGrid.x, m_MousePosGrid.y, m_Layer);
	m_CursorText.setString(ss.str());
	
	
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	if (!m_TextureSelector->getActive())
	{
		target.setView(m_View);
		target.draw(m_SelectorRect);
	}

	target.setView(m_Window->getDefaultView());
	m_TextureSelector->render(target);
	target.draw(m_Sidebar);

	target.setView(m_View);
	target.draw(m_CursorText);
	
}

void EditorState::updateEditorInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_CAMERA_UP"))))
	{
		m_View.move(0.f, -m_CameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		m_View.move(0.f, m_CameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		m_View.move(-m_CameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		m_View.move(m_CameraSpeed * dt, 0.f);
	}
	// add a tile to the tileMap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeytime())
	{
		if (!m_Sidebar.getGlobalBounds().contains(sf::Vector2f(m_MousePosWindow)))
		{
			if (!m_TextureSelector->getActive())
			{
				m_TileMap->addTile(m_MousePosGrid.x, m_MousePosGrid.y, 0, m_TextureRect, m_Collision, m_Type);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("TOGGLE_COLLISION"))) && getKeytime())
	{
		if (m_Collision)
			m_Collision = false;
		else
			m_Collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("INCREASE_TYPE"))) && getKeytime())
	{
		++m_Type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_Keybinds.at("DECREASE_TYPE"))) && getKeytime())
	{
		if(m_Type > 0)
			--m_Type;
	}
}

void EditorState::initVariables()
{
	m_TextureRect = sf::IntRect(0, 0, static_cast<int>(m_StateData->m_GridSize), static_cast<int>(m_StateData->m_GridSize));
	m_Collision = false;
	m_Type = TileTypes::DEFAULT;
	m_CameraSpeed = 100.f;
	m_Layer = 0;
}

void EditorState::initView()
{
	m_View.setSize(
		sf::Vector2f(
			static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.width),
			static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.height)
		)
	);
	m_View.setCenter(
		static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.width) / 2.f, 
		static_cast<float>(m_StateData->m_GfxSettings->m_Resolution.height) / 2.f
	);

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
	const sf::VideoMode& vm = m_StateData->m_GfxSettings->m_Resolution;
	m_Pmenu = new PauseMenu(m_StateData->m_GfxSettings->m_Resolution, m_Font);
	
	m_Pmenu->addButton("QUIT", GUI::p2pY(74.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Quit");
	m_Pmenu->addButton("SAVE", GUI::p2pY(46.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Save");
	m_Pmenu->addButton("LOAD", GUI::p2pY(37.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Load");
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
	m_TileMap = new TileMap(m_StateData->m_GridSize, 100, 100, "resources/images/tiles/tilesheet1.png");
}

void EditorState::initText()
{
	m_CursorText.setFont(m_Font);
	m_CursorText.setFillColor(sf::Color::White);
	m_CursorText.setCharacterSize(12);
	m_CursorText.setPosition(m_MousePosView.x, m_MousePosView.y);
}
