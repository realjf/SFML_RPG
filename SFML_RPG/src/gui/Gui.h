#pragma once


enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

namespace GUI {

	const float p2pX(const float perc, const sf::VideoMode& vm);
	const float p2pY(const float perc, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

	class Button
	{
	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);
		virtual ~Button();

		void render(sf::RenderTarget& target);
		void update(const sf::Vector2i& mousePosWindow);
		

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		void setText(const std::string text);
		void setId(const short unsigned id);
	private:
		short unsigned m_ButtonState;
		short unsigned m_ID;

		sf::RectangleShape m_Shape;
		sf::Font* m_Font;
		sf::Text m_Text;

		sf::Color m_IdleColor;
		sf::Color m_HoverColor;
		sf::Color m_ActiveColor;

		sf::Color m_OutlineIdleColor;
		sf::Color m_OutlineHoverColor;
		sf::Color m_OutlineActiveColor;

		sf::Color m_TextIdleColor;
		sf::Color m_TextHoverColor;
		sf::Color m_TextActiveColor;

	};


	class DropDownList
	{
	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaultIndex = 0);
		~DropDownList();

		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
		const bool getKeytime();
		void updateKeytime(const float& dt);
		const unsigned short& getActiveElementId() const;

	private:
		GUI::Button* m_ActiveElement;
		std::vector<GUI::Button*> m_List;
		sf::Font& m_Font;
		bool m_ShowList;
		float m_Keytime;
		float m_KeytimeMax;
	};

	class TextureSelector
	{
	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* textureSheet, sf::Font& font, std::string text);
		~TextureSelector();

		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
		void updateKeytime(const float& dt);
		const bool getKeytime();

	private:
		sf::RectangleShape m_Bounds;
		sf::Sprite m_Sheet;
		sf::RectangleShape m_Selector;
		sf::Vector2u m_MousePosGrid;
		sf::IntRect m_TextureRect;
		bool m_Active;
		float m_GridSize;
		bool m_Hidden;
		GUI::Button* m_HideBtn;
		float m_Keytime;
		const float m_KeytimeMax;
	};
}
