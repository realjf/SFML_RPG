#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: m_Font(font)
{
	m_Background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y)
	));
	m_Background.setFillColor(sf::Color(20, 20, 20, 100));

	m_Container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) - 100.f
		)
	);
	m_Container.setFillColor(sf::Color(20, 20, 20, 200));
	m_Container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - m_Container.getSize().x / 2.f,
		30.f
	);

	m_MenuText.setFont(font);
	m_MenuText.setFillColor(sf::Color(255, 255, 255, 200));
	m_MenuText.setCharacterSize(60);
	m_MenuText.setString("PAUSED");
	m_MenuText.setPosition(
		m_Container.getPosition().x + m_Container.getSize().x / 2.f - m_MenuText.getGlobalBounds().width / 2.f, 
		m_Container.getPosition().y + 40.f
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

void PauseMenu::update()
{

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
