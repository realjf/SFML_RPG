#pragma once
#include "Entity.h"

class Player :
    public Entity
{
public:
    Player(float x, float y, sf::Texture& textureSheet);
    virtual ~Player();

    virtual void update(const float& dt);
    void render(sf::RenderTarget& target);
    void updateAnimation(const float& dt);
    void updateAttack();
private:
    bool m_Attacking;

    void initVariables();
    void initComponents();

};

