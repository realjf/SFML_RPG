#pragma once

#include "components/MovementComponent.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual void move(const float x, const float y, const float& dt);
	virtual void setPosition(const float x, const float y);

	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

protected:
	sf::Sprite m_Sprite;
	
	MovementComponent* m_MovementComponent;

private:
	void initVariables();
};

