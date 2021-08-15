#pragma once
#include "Entity.h"

class Player :
    public Entity
{
public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();


private:
    void initVariables();
    void initComponents();

};

