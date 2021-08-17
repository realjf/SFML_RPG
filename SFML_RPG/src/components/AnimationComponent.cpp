#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: m_Sprite(sprite), m_TextureSheet(textureSheet), m_LastAnimation(NULL), m_PriorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : m_Animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, float animationTimer, int startframex, int startframey, int framesx, int framesy, int width, int height)
{
	m_Animations[key] = new Animation(m_Sprite, m_TextureSheet, animationTimer, startframex, startframey, framesx, framesy, width, height);
}

const bool& AnimationComponent::isDone(const std::string key)
{
	return m_Animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	if (m_PriorityAnimation)
	{
		if (m_PriorityAnimation == m_Animations[key])
		{
			if (m_LastAnimation != m_Animations[key])
			{
				if (m_LastAnimation == NULL)
					m_LastAnimation = m_Animations[key];
				else {
					m_LastAnimation->reset();
					m_LastAnimation = m_Animations[key];
				}
			}

			if (m_Animations[key]->play(dt))
			{
				m_PriorityAnimation = NULL;
			}
		}
	}
	else {
		if (priority)
		{
			m_PriorityAnimation = m_Animations[key];
		}

		if (m_LastAnimation != m_Animations[key])
		{
			if (m_LastAnimation == NULL)
				m_LastAnimation = m_Animations[key];
			else {
				m_LastAnimation->reset();
				m_LastAnimation = m_Animations[key];
			}
		}

		m_Animations[key]->play(dt);

	}

	return m_Animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float modifierMax, const bool priority)
{
	if (m_PriorityAnimation)
	{
		if (m_PriorityAnimation == m_Animations[key])
		{
			if (m_LastAnimation != m_Animations[key])
			{
				if (m_LastAnimation == NULL)
					m_LastAnimation = m_Animations[key];
				else {
					m_LastAnimation->reset();
					m_LastAnimation = m_Animations[key];
				}
			}

			if (m_Animations[key]->play(dt, abs(modifier / modifierMax)))
			{
				m_PriorityAnimation = NULL;
			}
		}
	}
	else {
		if (priority)
		{
			m_PriorityAnimation = m_Animations[key];
		}

		if (m_LastAnimation != m_Animations[key])
		{
			if (m_LastAnimation == NULL)
				m_LastAnimation = m_Animations[key];
			else {
				m_LastAnimation->reset();
				m_LastAnimation = m_Animations[key];
			}
		}

		m_Animations[key]->play(dt, abs(modifier / modifierMax));
	}

	return m_Animations[key]->isDone();
}
