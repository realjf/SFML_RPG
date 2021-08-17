#pragma once

#include "components/MovementComponent.h"
#include "components/AnimationComponent.h"
#include "components/HitboxComponent.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

	virtual void move(const float x, const float y, const float& dt);
	virtual void setPosition(const float x, const float y);

	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);
	void createHitboxComponent(sf::Sprite& sprite, const float offsetx, const float offsety, float width, float height);

protected:
	sf::Sprite m_Sprite;
	
	MovementComponent* m_MovementComponent;
	AnimationComponent* m_AnimationComponent;
	HitboxComponent* m_HitboxComponent;

private:
	void initVariables();
};

