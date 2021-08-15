#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	m_ButtonState = BTN_IDLE;

	m_Shape.setPosition(sf::Vector2f(x, y));
	m_Shape.setSize(sf::Vector2f(width, height));

	m_Font = font;
	m_Text.setFont(*m_Font);
	m_Text.setString(text);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(12);
	m_Text.setPosition(
		m_Shape.getPosition().x + m_Shape.getGlobalBounds().width / 2.f - m_Text.getGlobalBounds().width / 2.f,
		m_Shape.getPosition().y + m_Shape.getGlobalBounds().height / 2.f - m_Text.getGlobalBounds().height / 2.F
	);

	m_IdleColor = idleColor;
	m_HoverColor = hoverColor;
	m_ActiveColor = activeColor;

	m_Shape.setFillColor(m_IdleColor);
}

Button::~Button()
{

}

void Button::render(sf::RenderTarget* target)
{
	target->draw(m_Shape);
	target->draw(m_Text);
}

void Button::update(const sf::Vector2f mousePos)
{
	m_ButtonState = BTN_IDLE;
	if (m_Shape.getGlobalBounds().contains(mousePos))
	{
		m_ButtonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_ButtonState = BTN_ACTIVE;
		}
	}

	switch (m_ButtonState)
	{
	case BTN_IDLE:
		m_Shape.setFillColor(m_IdleColor);
		break;
	case BTN_HOVER:
		m_Shape.setFillColor(m_HoverColor);
		break;
	case BTN_ACTIVE:
		m_Shape.setFillColor(m_ActiveColor);
		break;
	default:
		m_Shape.setFillColor(sf::Color::Red);
		break;
	}
}

const bool Button::isPressed() const
{
	if (m_ButtonState == BTN_ACTIVE)
		return true;
	return false;
}
