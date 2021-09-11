#include "stdafx.h"
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player* player)
{
	m_Player = player;

	initFont();
	initHPBar();
}

PlayerGUI::~PlayerGUI()
{

}

void PlayerGUI::update(const float& dt)
{
	updateHPBar();
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderHPBar(target);
}

void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(m_Player->getAttributeComponent()->m_Hp) / static_cast<float>(m_Player->getAttributeComponent()->m_HpMax);
	m_HpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(m_HpBarMaxWidth * percent)),
			m_HpBarInner.getSize().y
		)
	);
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(m_HpBarBack);
	target.draw(m_HpBarInner);
}

void PlayerGUI::initFont()
{
	m_Font.loadFromFile("fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHPBar()
{
	float width = 300.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;
	m_HpBarMaxWidth = width;

	m_HpBarText.setFont(m_Font);


	m_HpBarBack.setSize(sf::Vector2f(width, height));
	m_HpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	m_HpBarBack.setPosition(x, y);

	m_HpBarInner.setSize(sf::Vector2f(width, height));
	m_HpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	m_HpBarInner.setPosition(m_HpBarBack.getPosition());
}
