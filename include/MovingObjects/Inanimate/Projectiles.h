#pragma once

#include "Inanimate.h"

class Projectiles : public Inanimate
{
public:
	Projectiles(const sf::Texture&, const sf::Vector2f&,const sf::Vector2f&, const sf::Vector2f&);

	virtual void update(const sf::Time& deltaTime) = 0;
};