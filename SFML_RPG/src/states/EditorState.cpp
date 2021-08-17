#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

EditorState::~EditorState()
{
	for (auto it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_Window;

	renderButtons(*target);
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
		endState();
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
			keybinds[key] = m_SupportedKeys->at(key2);
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
