#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	: m_Font(font)
{
	m_Background.setSize(sf::Vector2f(
		static_cast<float>(vm.width), 
		static_cast<float>(vm.height)
	));
	m_Background.setFillColor(sf::Color(20, 20, 20, 100));

	m_Container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - GUI::p2pY(9.3f, vm)
		)
	);
	m_Container.setFillColor(sf::Color(20, 20, 20, 200));
	m_Container.setPosition(
		static_cast<float>(vm.width) / 2.f - m_Container.getSize().x / 2.f,
		30.f
	);

	m_MenuText.setFont(font);
	m_MenuText.setFillColor(sf::Color(255, 255, 255, 200));
	m_MenuText.setCharacterSize(GUI::calcCharSize(vm));
	m_MenuText.setString("PAUSED");
	m_MenuText.setPosition(
		m_Container.getPosition().x + m_Container.getSize().x / 2.f - m_MenuText.getGlobalBounds().width / 2.f, 
		m_Container.getPosition().y + GUI::p2pY(4.f, vm)
	);
}

PauseMenu::~PauseMenu()
{
	auto it = m_Buttons.begin();
	for (it = m_Buttons.begin(); it != m_Buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : m_Buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(m_Background);
	target.draw(m_Container);

	for (auto& i : m_Buttons)
	{
		i.second->render(target);
	}

	target.draw(m_MenuText);
}

std::map<std::string, GUI::Button*>& PauseMenu::getButtons()
{
	return m_Buttons;
}

void PauseMenu::addButton(const std::string key, const float y, const float width, const float height, const unsigned charSize, const std::string text)
{
	float x = m_Container.getPosition().x + m_Container.getSize().x / 2.f - width / 2.f;

	m_Buttons[key] = new GUI::Button(x, y, width, height,
		&m_Font, text, charSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return m_Buttons[key]->isPressed();
}
