#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initGui();
	resetGui();
}

MainMenuState::~MainMenuState()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;

	target->draw(m_Background);
	renderButtons(*target);

	/*sf::Text mouseText;
	mouseText.setPosition(m_MousePosView.x + 20.0f, m_MousePosView.y);
	mouseText.setFont(m_Font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << m_MousePosView.x << " " << m_MousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

void MainMenuState::updateInput(const float& dt)
{

}


void MainMenuState::updateButtons()
{
	for (auto &it : m_Buttons)
	{
		it.second->update(m_MousePosWindow);
	}

	// new game
	if (m_Buttons["GAME_STAET"]->isPressed())
	{
		m_States->push(new GameState(m_StateData));
	}

	if (m_Buttons["SETTINGS_STATE"]->isPressed())
	{
		m_States->push(new SettingsState(m_StateData));
	}

	// editor
	if (m_Buttons["EDITOR_STATE"]->isPressed())
	{
		m_States->push(new EditorState(m_StateData));
	}

	// quit the game
	if (m_Buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : m_Buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	m_Background.setSize(
		sf::Vector2f(
			static_cast<float>(m_Window->getSize().x), 
			static_cast<float>(m_Window->getSize().y)
		)
	);

	
	if (!m_BackgroundTexture.loadFromFile("resources/images/backgrounds/bg1.png"))
	{
		throw("Error::MainMenuState::Failed_to_load_background_texture");
	}
	m_Background.setTexture(&m_BackgroundTexture);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

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

void MainMenuState::initFonts()
{
	if (!m_Font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		throw("Error::MainMenuState::Could_not_load_font");
	}
}

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = m_StateData->m_GfxSettings->m_Resolution;
	m_Buttons["GAME_STAET"] = new GUI::Button(
		GUI::p2pX(15.6f, vm), GUI::p2pY(44.4f, vm), 
		GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm),
		&m_Font, "New Game", GUI::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["SETTINGS_STATE"] = new GUI::Button(
		GUI::p2pX(15.6f, vm), GUI::p2pY(53.7f, vm),
		GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm),
		&m_Font, "Settings", GUI::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["EDITOR_STATE"] = new GUI::Button(
		GUI::p2pX(15.6f, vm), GUI::p2pY(63.f, vm),
		GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm),
		&m_Font, "Editor", GUI::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["EXIT_STATE"] = new GUI::Button(
		GUI::p2pX(15.6f, vm), GUI::p2pY(81.5f, vm),
		GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm),
		&m_Font, "Quit", GUI::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::resetGui()
{
	m_Buttons.clear();
	initGui();
}
