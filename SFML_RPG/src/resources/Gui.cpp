#include "stdafx.h"
#include "Gui.h"

namespace GUI {
	Button::Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned characterSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
		sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
		short unsigned id)
	{
		m_ButtonState = BTN_IDLE;
		m_ID = id;

		m_Shape.setPosition(sf::Vector2f(x, y));
		m_Shape.setSize(sf::Vector2f(width, height));
		m_Shape.setFillColor(m_IdleColor);

		m_Shape.setOutlineThickness(1.f);
		m_Shape.setOutlineColor(outlineIdleColor);

		m_Font = font;
		m_Text.setFont(*m_Font);
		m_Text.setString(text);
		m_Text.setFillColor(m_TextIdleColor);
		m_Text.setCharacterSize(characterSize);
		m_Text.setPosition(
			m_Shape.getPosition().x + (m_Shape.getGlobalBounds().width / 2.f) - m_Text.getGlobalBounds().width / 2.f,
			m_Shape.getPosition().y + (m_Shape.getGlobalBounds().height / 2.f) - m_Text.getGlobalBounds().height / 2.f
		);

		m_IdleColor = idleColor;
		m_HoverColor = hoverColor;
		m_ActiveColor = activeColor;

		m_TextIdleColor = textIdleColor;
		m_TextHoverColor = textHoverColor;
		m_TextActiveColor = textActiveColor;

		m_OutlineIdleColor = outlineIdleColor;
		m_OutlineHoverColor = outlineHoverColor;
		m_OutlineActiveColor = outlineActiveColor;
	}

	Button::~Button()
	{

	}

	void Button::render(sf::RenderTarget& target)
	{
		target.draw(m_Shape);
		target.draw(m_Text);
	}

	void Button::update(const sf::Vector2f& mousePos)
	{
		m_ButtonState = BTN_IDLE;

		if (m_Shape.getGlobalBounds().contains(mousePos))
		{
			m_ButtonState = BTN_HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				m_ButtonState = BTN_ACTIVE;
		}

		switch (m_ButtonState)
		{
		case BTN_IDLE:
			m_Shape.setFillColor(m_IdleColor);
			m_Text.setFillColor(m_TextIdleColor);
			m_Shape.setOutlineColor(m_OutlineIdleColor);
			break;
		case BTN_HOVER:
			m_Shape.setFillColor(m_HoverColor);
			m_Text.setFillColor(m_TextHoverColor);
			m_Shape.setOutlineColor(m_OutlineHoverColor);
			break;
		case BTN_ACTIVE:
			m_Shape.setFillColor(m_ActiveColor);
			m_Text.setFillColor(m_TextActiveColor);
			m_Shape.setOutlineColor(m_OutlineActiveColor);
			break;
		default:
			m_Shape.setFillColor(sf::Color::Red);
			m_Text.setFillColor(sf::Color::Blue);
			m_Shape.setOutlineColor(sf::Color::Green);
			break;
		}
	}

	const bool Button::isPressed() const
	{
		if (m_ButtonState == BTN_ACTIVE)
			return true;
		return false;
	}

	const std::string Button::getText() const
	{
		return m_Text.getString();
	}

	const short unsigned& Button::getId() const
	{
		return m_ID;
	}

	void Button::setText(const std::string text)
	{
		m_Text.setString(text);
	}

	void Button::setId(const short unsigned id)
	{
		m_ID = id;
	}

	DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaultIndex)
		: m_Font(font), m_ShowList(false), m_KeytimeMax(1.f), m_Keytime(0.f)
	{
		//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

		m_ActiveElement = new GUI::Button(
			x, y, width, height,
			&m_Font, list[defaultIndex], 14,
			sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
		);


		for (size_t i = 0; i < nrOfElements; i++)
		{
			m_List.push_back(
				new GUI::Button(x, y + ((i+1) * height), width, height,
					&m_Font, list[i], 14,
					sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
					sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				i)
			);
		}
	}

	DropDownList::~DropDownList()
	{
		delete m_ActiveElement;
		for (size_t i = 0; i < m_List.size(); i++)
		{
			delete m_List[i];
		}
	}

	void DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
	{
		updateKeytime(dt);

		m_ActiveElement->update(mousePos);

		if (m_ActiveElement->isPressed() && getKeytime())
		{
			if (m_ShowList)
				m_ShowList = false;
			else
				m_ShowList = true;
		}

		if (m_ShowList) 
		{
			for (auto& i : m_List)
			{
				i->update(mousePos);

				if (i->isPressed() && getKeytime())
				{
					m_ShowList = false;
					m_ActiveElement->setText(i->getText());
					m_ActiveElement->setId(i->getId());
				}
			}
		}
		

	}

	void DropDownList::render(sf::RenderTarget& target)
	{
		m_ActiveElement->render(target);

		if (m_ShowList)
		{
			for (auto& i : m_List)
			{
				i->render(target);
			}
		}
	}

	const bool DropDownList::getKeytime()
	{
		if (m_Keytime >= m_KeytimeMax)
		{
			m_Keytime = 0.f;
			return true;
		}

		return false;
	}

	void DropDownList::updateKeytime(const float& dt)
	{
		if (m_Keytime < m_KeytimeMax)
			m_Keytime += 10.f * dt;
	}

	const unsigned short& DropDownList::getActiveElementId() const
	{
		return m_ActiveElement->getId();
	}

}
