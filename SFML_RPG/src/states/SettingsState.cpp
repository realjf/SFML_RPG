#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states), m_GfxSettings(gfxSettings)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initGui();
	initText();
}

SettingsState::~SettingsState()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}

	for (auto it = m_DropDownLists.begin(); it != m_DropDownLists.end(); ++it)
	{
		delete it->second;
	}
}

void SettingsState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateGui(dt);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;

	target->draw(m_Background);
	renderGui(*target);

	target->draw(m_OptionsText);

	sf::Text mouseText;
	mouseText.setPosition(m_MousePosView.x + 20.0f, m_MousePosView.y);
	mouseText.setFont(m_Font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << m_MousePosView.x << " " << m_MousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}

void SettingsState::updateInput(const float& dt)
{

}


void SettingsState::updateGui(const float& dt)
{
	for (auto& it : m_Buttons)
	{
		it.second->update(m_MousePosView);
	}

	// quit the game
	if (m_Buttons["BACK"]->isPressed())
	{
		endState();
	}

	if (m_Buttons["APPLY"]->isPressed())
	{
		m_GfxSettings.m_Resolution = m_Modes[m_DropDownLists["RESOLUTION"]->getActiveElementId()];

		m_Window->create(m_GfxSettings.m_Resolution, m_GfxSettings.m_Title, sf::Style::Default);
	}

	for (auto& it : m_DropDownLists)
	{
		it.second->update(m_MousePosView, dt);
	}
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : m_Buttons)
	{
		it.second->render(target);
	}

	for (auto& it : m_DropDownLists)
	{
		it.second->render(target);
	}
}


void SettingsState::initVariables()
{
	m_Modes = sf::VideoMode::getFullscreenModes();
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

void SettingsState::initGui()
{
	m_Buttons["BACK"] = new GUI::Button(
		1500.f, 880.f, 250.f, 50.f,
		&m_Font, "Back", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	m_Buttons["APPLY"] = new GUI::Button(
		1300.f, 880.f, 250.f, 50.f,
		&m_Font, "Apply", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : m_Modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	m_DropDownLists["RESOLUTION"] = new GUI::DropDownList(800, 450, 200, 50, m_Font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	m_OptionsText.setFont(m_Font);

	m_OptionsText.setPosition(sf::Vector2f(100.f, 450.f));
	m_OptionsText.setCharacterSize(30);
	m_OptionsText.setFillColor(sf::Color(255, 255, 255, 200));

	m_OptionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}
