#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
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
		it.second->update(m_MousePosView);
	}

	// new game
	if (m_Buttons["GAME_STAET"]->isPressed())
	{
		m_States->push(new GameState(m_Window, m_SupportedKeys, m_States));
	}

	if (m_Buttons["SETTINGS_STATE"]->isPressed())
	{
		m_States->push(new SettingsState(m_Window, m_SupportedKeys, m_States));
	}

	// editor
	if (m_Buttons["EDITOR_STATE"]->isPressed())
	{
		m_States->push(new EditorState(m_Window, m_SupportedKeys, m_States));
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
			keybinds[key] = m_SupportedKeys->at(key2);
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

void MainMenuState::initButtons()
{
	m_Buttons["GAME_STAET"] = new Button(300.f, 480.f, 250.f, 50.f,
		&m_Font, "New Game", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["SETTINGS_STATE"] = new Button(300.f, 580.f, 250.f, 50.f,
		&m_Font, "Settings", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["EDITOR_STATE"] = new Button(300.f, 680.f, 250.f, 50.f,
		&m_Font, "Editor", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["EXIT_STATE"] = new Button(300.f, 880.f, 250.f, 50.f,
		&m_Font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}
