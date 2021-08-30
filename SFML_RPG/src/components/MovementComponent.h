#pragma once


enum movement_states { 
	IDLE = 0,
	MOVING,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP,
	MOVING_DONW
};

class MovementComponent
{

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	void update(const float& dt);
	void move(const float x, const float y, const float& dt);

	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;

	const bool getState(const short unsigned state) const;

private:
	sf::Sprite& m_Sprite;

	float m_MaxVelocity;
	sf::Vector2f m_Velocity;
	float m_Acceleration;
	float m_Deceleration;


};

