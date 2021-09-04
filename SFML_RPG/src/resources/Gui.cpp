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




	TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, 
		const sf::Texture* textureSheet, sf::Font& font, std::string text)
	{
		m_Active = false;
		m_GridSize = gridSize;
		m_Hidden = false;
		float offset = 60.f;

		m_Bounds.setSize(sf::Vector2f(width, height));
		m_Bounds.setPosition(x + offset, y);
		m_Bounds.setFillColor(sf::Color(50, 50, 50, 100));
		m_Bounds.setOutlineThickness(1.f);
		m_Bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

		m_Sheet.setTexture(*textureSheet);
		m_Sheet.setPosition(x + offset, y);

		if (m_Sheet.getGlobalBounds().width > m_Bounds.getGlobalBounds().width)
		{
			m_Sheet.setTextureRect(sf::IntRect(0, 0, m_Bounds.getGlobalBounds().width, m_Sheet.getGlobalBounds().height));
		}
		if (m_Sheet.getGlobalBounds().height > m_Bounds.getGlobalBounds().height)
		{
			m_Sheet.setTextureRect(sf::IntRect(0, 0, m_Sheet.getGlobalBounds().width, m_Bounds.getGlobalBounds().height));
		}

		m_Selector.setPosition(x + offset, y);
		m_Selector.setSize(sf::Vector2f(gridSize, gridSize));
		m_Selector.setFillColor(sf::Color::Transparent);
		m_Selector.setOutlineThickness(1.f);
		m_Selector.setOutlineColor(sf::Color::Red);

		m_TextureRect.width = static_cast<int>(gridSize);
		m_TextureRect.height = static_cast<int>(gridSize);
		
		m_HideBtn = new GUI::Button(y, x, 50.f, 50.f,
			&font, text, 30,
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	}

	TextureSelector::~TextureSelector()
	{
		delete m_HideBtn;
	}

	const bool& TextureSelector::getActive() const
	{
		return m_Active;
	}

	const sf::IntRect& TextureSelector::getTextureRect() const
	{
		return m_TextureRect;
	}

	void TextureSelector::update(const sf::Vector2i& mousePosWindow)
	{
		m_HideBtn->update(static_cast<sf::Vector2f>(mousePosWindow));

		if (m_HideBtn->isPressed())
		{
			if (m_Hidden)
				m_Hidden = false;
			else
				m_Hidden = true;
		}

		if (!m_Hidden)
		{
			if (m_Bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
				m_Active = true;
			else
				m_Active = false;

			if (m_Active)
			{
				m_MousePosGrid.x = (mousePosWindow.x - static_cast<int>(m_Bounds.getPosition().x)) / static_cast<unsigned>(m_GridSize);
				m_MousePosGrid.y = (mousePosWindow.y - static_cast<int>(m_Bounds.getPosition().y)) / static_cast<unsigned>(m_GridSize);
				m_Selector.setPosition(
					m_Bounds.getPosition().x + m_MousePosGrid.x * m_GridSize,
					m_Bounds.getPosition().y + m_MousePosGrid.y * m_GridSize
				);

				m_TextureRect.left = static_cast<int>(m_Selector.getPosition().x - m_Bounds.getPosition().x);
				m_TextureRect.top = static_cast<int>(m_Selector.getPosition().y - m_Bounds.getPosition().y);
			}
		}
		
	}

	void TextureSelector::render(sf::RenderTarget& target)
	{
		

		if (!m_Hidden)
		{
			target.draw(m_Bounds);
			target.draw(m_Sheet);

			if (m_Active)
				target.draw(m_Selector);
		}

		m_HideBtn->render(target);
	}

}
