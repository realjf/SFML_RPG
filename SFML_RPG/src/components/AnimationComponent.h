#pragma once

#include <iostream>
#include <string>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class AnimationComponent
{
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float modifierMax, const bool priority = false);
	void addAnimation(const std::string key, float animationTimer, int startframex, int startframey, int framesx, int framesy, int width, int height);

	const bool& isDone(const std::string key);

private:
	class Animation
	{
	public:
		sf::Sprite& m_Sprite;
		sf::Texture& m_TextureSheet;
		float m_AnimationTimer;
		int m_Width;
		int m_Height;
		float m_Timer;
		bool m_Done;
		sf::IntRect m_StartRect;
		sf::IntRect m_CurrentRect;
		sf::IntRect m_EndRect;

		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, int startframex, int startframey, int framesx, int framesy, int width, int height)
			: m_Sprite(sprite), m_Timer(0.f), m_Done(false), m_TextureSheet(textureSheet), m_AnimationTimer(animationTimer), m_Width(width), m_Height(height)
		{
			m_Timer = 0.f;
			m_StartRect = sf::IntRect(startframex * width, startframey * height, width, height);
			m_EndRect = sf::IntRect(framesx * width, framesy * height, width, height);
			m_CurrentRect = m_StartRect;

			m_Sprite.setTexture(m_TextureSheet, true);
			m_Sprite.setTextureRect(m_StartRect);
		}

		const bool& isDone() const
		{
			return m_Done;
		}

		const bool& play(const float& dt)
		{
			m_Done = false;
			m_Timer += 100.f * dt;
			if (m_Timer >= m_AnimationTimer)
			{
				m_Timer = 0.f;
				if (m_CurrentRect != m_EndRect)
				{
					m_CurrentRect.left += m_Width;
				}
				else {
					m_CurrentRect.left = m_StartRect.left;
					m_Done = true;
				}

				m_Sprite.setTextureRect(m_CurrentRect);
			}

			return m_Done;
		}

		const bool& play(const float& dt, float modPercent)
		{
			if (modPercent < 0.5f)
				modPercent = 0.5f;
			m_Done = false;
			m_Timer += modPercent * 100.f * dt;
			if (m_Timer >= m_AnimationTimer)
			{
				m_Timer = 0.f;
				if (m_CurrentRect != m_EndRect)
				{
					m_CurrentRect.left += m_Width;
				}
				else {
					m_CurrentRect.left = m_StartRect.left;
					m_Done = true;
				}

				m_Sprite.setTextureRect(m_CurrentRect);
			}

			return m_Done;
		}

		void reset()
		{
			m_Timer = 0.f;
			m_CurrentRect = m_StartRect;
		}
	};

	std::map<std::string, Animation*> m_Animations;
	sf::Sprite& m_Sprite;
	sf::Texture& m_TextureSheet;
	Animation* m_LastAnimation;
	Animation* m_PriorityAnimation;
};

