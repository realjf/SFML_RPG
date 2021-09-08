#pragma once

#include "components/MovementComponent.h"
#include "components/AnimationComponent.h"
#include "components/HitboxComponent.h"


class HitboxComponent;
class MovementComponent;
class AnimationComponent;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	virtual void move(const float x, const float y, const float& dt);
	virtual void setPosition(const float x, const float y);
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

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

