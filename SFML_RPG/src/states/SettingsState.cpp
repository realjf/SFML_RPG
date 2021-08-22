#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

SettingsState::~SettingsState()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
}

void SettingsState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void SettingsState::render(sf::RenderTarget* target)
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

void SettingsState::updateInput(const float& dt)
{

}


void SettingsState::updateButtons()
{
	for (auto& it : m_Buttons)
	{
		it.second->update(m_MousePosView);
	}

	// quit the game
	if (m_Buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : m_Buttons)
	{
		it.second->render(target);
	}
}


void SettingsState::initVariables()
{

}

void SettingsState::initBackground()
{
	m_Background.setSize(
		sf::Vector2f(
			static_cast<float>(m_Window->getSize().x),
			static_cast<float>(m_Window->getSize().y)
		)
	);


	if (!m_BackgroundTexture.loadFromFile("resources/images/backgrounds/bg1.png"))
	{
		throw("Error::SettingsState::Failed_to_load_background_texture");
	}
	m_Background.setTexture(&m_BackgroundTexture);
}

void SettingsState::initKeybinds()
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

void SettingsState::initFonts()
{
	if (!m_Font.loadFromFile("fonts/Dosis-Light.ttf"))
	{
		throw("Error::SettingsState::Could_not_load_font");
	}
}

void SettingsState::initButtons()
{
	m_Buttons["EXIT_STATE"] = new GUI::Button(300.f, 880.f, 250.f, 50.f,
		&m_Font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}