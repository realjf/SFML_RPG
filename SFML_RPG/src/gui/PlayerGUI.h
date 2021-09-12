#pragma once

#include "entities/Player.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
public:
	PlayerGUI(Player* player);
	~PlayerGUI();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
	void updateHPBar();
	void updateEXPBar();
	void renderHPBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);

private:
	Player* m_Player;
	sf::Font m_Font;

	// hp bar
	sf::RectangleShape m_HpBarBack;
	sf::RectangleShape m_HpBarInner;
	float m_HpBarMaxWidth;
	sf::Text m_HpBarText;
	std::string m_HpBarString;

	// exp bar
	sf::RectangleShape m_ExpBarBack;
	sf::RectangleShape m_ExpBarInner;
	float m_ExpBarMaxWidth;
	sf::Text m_ExpBarText;
	std::string m_ExpBarString;

	void initFont();
	void initHPBar();
	void initEXPBar();

};

