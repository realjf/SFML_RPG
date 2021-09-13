#include "stdafx.h"
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player* player)
{
	m_Player = player;

	initFont();
	initHPBar();
	initEXPBar();
	initLevelBar();
}

PlayerGUI::~PlayerGUI()
{

}

void PlayerGUI::update(const float& dt)
{
	updateHPBar();
	updateEXPBar();
	updateLevelBar();
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderHPBar(target);
	renderEXPBar(target);
	renderLevelBar(target);
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

	m_HpBarString = std::to_string(m_Player->getAttributeComponent()->m_Hp) + "/" + std::to_string(m_Player->getAttributeComponent()->m_HpMax);
	m_HpBarText.setString(m_HpBarString);
}

void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(m_Player->getAttributeComponent()->m_Exp) / static_cast<float>(m_Player->getAttributeComponent()->m_ExpNext);

	m_ExpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(m_ExpBarMaxWidth * percent)),
			m_ExpBarInner.getSize().y
		)
	);

	m_ExpBarString = std::to_string(m_Player->getAttributeComponent()->m_Exp) + "/" + std::to_string(m_Player->getAttributeComponent()->m_ExpNext);
	m_ExpBarText.setString(m_ExpBarString);
}

void PlayerGUI::updateLevelBar()
{
	m_LevelBarString = std::to_string(m_Player->getAttributeComponent()->m_Level);
	m_LevelBarText.setString(m_LevelBarString);
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(m_HpBarBack);
	target.draw(m_HpBarInner);
	target.draw(m_HpBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	target.draw(m_ExpBarBack);
	target.draw(m_ExpBarInner);
	target.draw(m_ExpBarText);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(m_LevelBarBack);
	target.draw(m_LevelBarText);
}

void PlayerGUI::initFont()
{
	m_Font.loadFromFile("fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHPBar()
{
	float width = 200.f;
	float height = 30.f;
	float x = 20.f;
	float y = 90.f;
	m_HpBarMaxWidth = width;


	m_HpBarBack.setSize(sf::Vector2f(width, height));
	m_HpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	m_HpBarBack.setPosition(x, y);

	m_HpBarInner.setSize(sf::Vector2f(width, height));
	m_HpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	m_HpBarInner.setPosition(m_HpBarBack.getPosition());	
	
	m_HpBarText.setFont(m_Font);
	m_HpBarText.setCharacterSize(14);
	m_HpBarText.setPosition(m_HpBarInner.getPosition().x + 10.f, m_HpBarInner.getPosition().y + 5.f);
}

void PlayerGUI::initEXPBar()
{
	float width = 200.f;
	float height = 30.f;
	float x = 20.f;
	float y = 60.f;
	m_ExpBarMaxWidth = width;


	m_ExpBarBack.setSize(sf::Vector2f(width, height));
	m_ExpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	m_ExpBarBack.setPosition(x, y);

	m_ExpBarInner.setSize(sf::Vector2f(width, height));
	m_ExpBarInner.setFillColor(sf::Color(20, 20, 250, 200));
	m_ExpBarInner.setPosition(m_ExpBarBack.getPosition());

	m_ExpBarText.setFont(m_Font);
	m_ExpBarText.setCharacterSize(12);
	m_ExpBarText.setPosition(m_ExpBarInner.getPosition().x + 10.f, m_ExpBarInner.getPosition().y + 5.f);
}

void PlayerGUI::initLevelBar()
{
	float width = 30.f;
	float height = 30.f;
	float x = 20.f;
	float y = 20.f;


	m_LevelBarBack.setSize(sf::Vector2f(width, height));
	m_LevelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	m_LevelBarBack.setPosition(x, y);

	m_LevelBarText.setFont(m_Font);
	m_LevelBarText.setCharacterSize(18);
	m_LevelBarText.setPosition(m_LevelBarBack.getPosition().x + 10.f, m_LevelBarBack.getPosition().y + 5.f);
}
