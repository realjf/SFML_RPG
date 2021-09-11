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
	void renderHPBar(sf::RenderTarget& target);

private:
	Player* m_Player;
	sf::RectangleShape m_HpBarBack;
	sf::RectangleShape m_HpBarInner;
	sf::Font m_Font;
	float m_HpBarMaxWidth;
	sf::Text m_HpBarText;

	void initFont();
	void initHPBar();

};

