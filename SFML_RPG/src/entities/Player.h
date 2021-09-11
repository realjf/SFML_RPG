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
    AttributeComponent* getAttributeComponent();
    void loseHP(const int hp);
    void loseEXP(const unsigned exp);
    void gainHP(const int hp);
    void gainEXP(const unsigned exp);

private:
    bool m_Attacking;

    void initVariables();
    void initComponents();

};

